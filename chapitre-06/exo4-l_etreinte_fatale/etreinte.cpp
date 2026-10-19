#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKThreading/NkThread.h"
#include "NKTime/NkChrono.h"
#include "NKThreading/NkScopedLock.h"
#include "NKThreading/NkMutex.h"

#include <iostream>

// ---------------------------------------------------------------------------
// VERSION QUI SE FIGE (etreinte fatale) -- laissee en commentaire.
// Le fil a prend m1 puis m2 ; le fil b prend m2 puis m1. Chaque fil attend
// 100 ms entre ses deux verrous : le blocage est alors systematique.
//
// nkentseu::threading::NkMutex m1;
// nkentseu::threading::NkMutex m2;
//
// nkentseu::threading::NkThread a([&](void*) {
//     nkentseu::threading::NkScopedLock<nkentseu::threading::NkMutex> guard(m1);
//     nkentseu::NkChrono::SleepMilliseconds(100);
//     nkentseu::threading::NkScopedLock<nkentseu::threading::NkMutex> lock(m2);
// });
//
// nkentseu::threading::NkThread b([&](void*) {
//     nkentseu::threading::NkScopedLock<nkentseu::threading::NkMutex> lock(m2);
//     nkentseu::NkChrono::SleepMilliseconds(100);
//     nkentseu::threading::NkScopedLock<nkentseu::threading::NkMutex> guard(m1);
// });
//
// a.SetName("Thread A");
// b.SetName("Thread B");
// a.Join();
// b.Join();
// ---------------------------------------------------------------------------

int nkmain(const nkentseu::NkEntryState& state) {
    (void)state;

    nkentseu::threading::NkMutex m1;
    nkentseu::threading::NkMutex m2;

    // VERSION CORRIGEE : les deux fils prennent les verrous dans le meme
    // ordre (m1 puis m2). Les deux verrous et les deux attentes de 100 ms
    // sont conserves ; seul l'ordre d'acquisition change.
    nkentseu::threading::NkThread a([&](void*) {
        nkentseu::threading::NkScopedLock<nkentseu::threading::NkMutex> guard(m1);
        nkentseu::NkChrono::SleepMilliseconds(100);
        nkentseu::threading::NkScopedLock<nkentseu::threading::NkMutex> lock(m2);
    });

    nkentseu::threading::NkThread b([&](void*) {
        nkentseu::threading::NkScopedLock<nkentseu::threading::NkMutex> guard(m1);
        nkentseu::NkChrono::SleepMilliseconds(100);
        nkentseu::threading::NkScopedLock<nkentseu::threading::NkMutex> lock(m2);
    });

    a.SetName("Thread A");
    b.SetName("Thread B");

    a.Join();
    b.Join();

    std::cout << "Les deux fils sont termines : pas d'etreinte." << std::endl;

    return 0;
}