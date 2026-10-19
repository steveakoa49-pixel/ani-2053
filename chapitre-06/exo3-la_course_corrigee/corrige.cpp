#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKThreading/NkThread.h"
#include "NKContainers/Sequential/NkVector.h"
#include "NKTime/NkChrono.h"
#include "NKThreading/NkScopedLock.h"
#include "NKThreading/NkMutex.h"
#include "NKCore/NkAtomic.h"

#include <iostream>

// Chaque version : 8 fils, 1 000 000 d'increments par fil, total attendu 8 000 000.

int nkmain(const nkentseu::NkEntryState& state) {
    (void)state;

    nkentseu::NkChrono chrono;

    // ------------------------------------------------------------------
    // Version sans protection
    // ------------------------------------------------------------------
    int counterUnsafe = 0;
    nkentseu::NkVector<nkentseu::threading::NkThread> threadsUnsafe;
    threadsUnsafe.Reserve(8);
    for (int i = 0; i < 8; ++i) {
        threadsUnsafe.EmplaceBack([&](auto&&...) {
            for (int j = 0; j < 1000000; ++j)
                counterUnsafe += 1;
        });
    }
    for (auto& t : threadsUnsafe)
        t.Join();

    std::cout << "Sans protection attendue : 8000000 -- obtenue : "
              << counterUnsafe << std::endl;
    std::cout << "Temps ecoule : " << chrono.Reset().milliseconds << " ms" << std::endl;

    // ------------------------------------------------------------------
    // Version mutex + verrou de portee (NkScopedLock)
    // ------------------------------------------------------------------
    int counterMutex = 0;
    nkentseu::threading::NkMutex mutex;
    nkentseu::NkVector<nkentseu::threading::NkThread> threadsMutex;
    threadsMutex.Reserve(8);
    for (int i = 0; i < 8; ++i) {
        threadsMutex.EmplaceBack([&](auto&&...) {
            for (int j = 0; j < 1000000; ++j) {
                // Verrou pris autour de l'increment seul, pas autour de la boucle.
                nkentseu::threading::NkScopedLock<nkentseu::threading::NkMutex> lock(mutex);
                counterMutex += 1;
            }
        });
    }
    for (auto& t : threadsMutex)
        t.Join();

    std::cout << "Mutex attendue : 8000000 -- obtenue : "
              << counterMutex << std::endl;
    std::cout << "Temps ecoule : " << chrono.Reset().milliseconds << " ms" << std::endl;

    // ------------------------------------------------------------------
    // Version atomique (NkAtomic + FetchAdd)
    // ------------------------------------------------------------------
    nkentseu::NkAtomic<int> counterAtomic{0};
    nkentseu::NkVector<nkentseu::threading::NkThread> threadsAtomic;
    threadsAtomic.Reserve(8);
    for (int i = 0; i < 8; ++i) {
        threadsAtomic.EmplaceBack([&](auto&&...) {
            for (int j = 0; j < 1000000; ++j)
                counterAtomic.FetchAdd(1);
        });
    }
    for (auto& t : threadsAtomic)
        t.Join();

    std::cout << "Atomique attendue : 8000000 -- obtenue : "
              << counterAtomic << std::endl;
    std::cout << "Temps ecoule : " << chrono.Reset().milliseconds << " ms" << std::endl;

    // ------------------------------------------------------------------
    // Version locale : chaque fil compte dans sa propre variable.
    // Les totaux ne sont lus qu'apres les Join.
    // ------------------------------------------------------------------
    nkentseu::NkVector<int> locals;
    locals.Resize(8, 0);

    nkentseu::NkVector<nkentseu::threading::NkThread> threadsLocal;
    threadsLocal.Reserve(8);
    for (int i = 0; i < 8; ++i) {
        threadsLocal.EmplaceBack([&, i](auto&&...) {
            for (int j = 0; j < 1000000; ++j)
                locals[i] += 1;
        });
    }
    for (auto& t : threadsLocal)
        t.Join();

    int totalLocal = 0;
    for (int i = 0; i < static_cast<int>(locals.Size()); ++i)
        totalLocal += locals[i];

    std::cout << "Local attendue : 8000000 -- obtenue : "
              << totalLocal << std::endl;
    std::cout << "Temps ecoule : " << chrono.Reset().milliseconds << " ms" << std::endl;

    return 0;
}