#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKThreading/NkThreadPool.h"
#include "NKThreading/NkThread.h"
#include "NKContainers/Sequential/NkVector.h"
#include "NKTime/NkChrono.h"
#include "NKTime/NkElapsedTime.h"

#include <iostream>
#include <cstdint>

// Tâche courte : additionner 1000 entiers dans une variable locale.
// Le résultat est retourné et accumulé par l'appelant pour empêcher
// le compilateur de la retirer en Release.
static std::int64_t ShortTask(std::int64_t iterations) {
    std::int64_t sum = 0;
    for (std::int64_t i = 0; i < iterations; ++i) {
        sum += i;
    }
    return sum;
}

// Mesure une version "réserve de fils" : 200 tâches soumises à une NkThreadPool.
static double MeasurePool(nkentseu::threading::NkThreadPool& pool,
                          std::int64_t iterations,
                          std::int64_t& accumulator) {
    nkentseu::NkChrono chrono;

    nkentseu::NkVector<std::int64_t> results;
    results.Resize(200);

    for (int i = 0; i < 200; ++i) {
        pool.Enqueue([&, i]() {
            results[i] = ShortTask(iterations);
        });
    }
    pool.Join();

    // Garde le résultat visible pour empêcher l'optimisation en Release.
    std::int64_t total = 0;
    for (int i = 0; i < 200; ++i) {
        total += results[i];
    }
    accumulator += total;

    return chrono.Reset().milliseconds;
}

// Mesure une version "fils créés à la main" : 200 NkThread joints.
static double MeasureThreads(std::int64_t iterations,
                             std::int64_t& accumulator) {
    nkentseu::NkChrono chrono;

    nkentseu::NkVector<std::int64_t> results;
    results.Resize(200);

    nkentseu::NkVector<nkentseu::threading::NkThread> threads;
    threads.Reserve(200);

    for (int i = 0; i < 200; ++i) {
        threads.EmplaceBack([&, i]() {
            results[i] = ShortTask(iterations);
        });
    }
    for (int i = 0; i < static_cast<int>(threads.Size()); ++i) {
        threads[i].Join();
    }

    std::int64_t total = 0;
    for (int i = 0; i < 200; ++i) {
        total += results[i];
    }
    accumulator += total;

    return chrono.Reset().milliseconds;
}

int nkmain(const nkentseu::NkEntryState& state) {
    (void)state;

    const std::int64_t shortIterations = 1000;
    const std::int64_t longIterations  = shortIterations * 100;

    std::int64_t accumulator = 0;

    // ------------------------------------------------------------------
    // Tâche courte
    // ------------------------------------------------------------------
    std::cout << "=== Tache courte (" << shortIterations << " iterations) ===" << std::endl;

    nkentseu::threading::NkThreadPool pool;
    const unsigned int numWorkers = pool.GetNumWorkers();
    std::cout << "Ouvriers : " << numWorkers << std::endl;

    double poolTimes[3]   = {};
    double threadTimes[3] = {};

    for (int m = 0; m < 3; ++m) {
        poolTimes[m] = MeasurePool(pool, shortIterations, accumulator);
        std::cout << "  Reserve  mesure " << (m + 1) << " : "
                  << poolTimes[m] << " ms" << std::endl;
    }
    for (int m = 0; m < 3; ++m) {
        threadTimes[m] = MeasureThreads(shortIterations, accumulator);
        std::cout << "  Fils     mesure " << (m + 1) << " : "
                  << threadTimes[m] << " ms" << std::endl;
    }

    // ------------------------------------------------------------------
    // Tâche longue (100x plus longue)
    // ------------------------------------------------------------------
    std::cout << "=== Tache longue (" << longIterations << " iterations) ===" << std::endl;

    double poolLong   = MeasurePool(pool, longIterations, accumulator);
    double threadLong = MeasureThreads(longIterations, accumulator);
    std::cout << "  Reserve : " << poolLong   << " ms" << std::endl;
    std::cout << "  Fils    : " << threadLong << " ms" << std::endl;

    // Résultat affiché pour empêcher l'élimination de la tâche en Release.
    std::cout << "Resultat (garde anti-optimisation) : " << accumulator << std::endl;

    return 0;
}