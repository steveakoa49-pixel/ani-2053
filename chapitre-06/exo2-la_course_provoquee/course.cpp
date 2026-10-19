#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKThreading/NkThread.h"
#include "NKContainers/Sequential/NkVector.h"

#include <iostream>

int nkmain(const nkentseu::NkEntryState& state) {
    (void)state;

    // Compteur partage, sans aucune protection (course volontaire).
    int counter = 0;

    // Huit fils, un million d'increments chacun, tous joints.
    nkentseu::NkVector<nkentseu::threading::NkThread> threads;
    threads.Reserve(8);
    for (int i = 0; i < 8; ++i) {
        threads.EmplaceBack([&](auto&&...) {
            for (int j = 0; j < 1000000; ++j)
                counter += 1;
        });
    }
    for (auto& t : threads)
        t.Join();

    std::cout << "Valeur du compteur attendue : 8000000 -- valeur obtenue : "
              << counter << std::endl;

    // Seconde version : un seul fil, un million d'increments.
    counter = 0;
    for (int i = 0; i < 1000000; ++i)
        counter += 1;

    std::cout << "Valeur du compteur attendue : 1000000 -- valeur obtenue : "
              << counter << std::endl;

    return 0;
}