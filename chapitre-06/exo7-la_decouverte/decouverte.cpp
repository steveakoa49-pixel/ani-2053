#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKNetwork/NKNetwork.h"
#include "NKTime/NkClock.h"
#include "NKTime/NkChrono.h"

#include <cstring>

enum class NetRole {
    NONE,
    SERVER,
    CLIENT
};

int nkmain(const nkentseu::NkEntryState& state) {
    NetRole role = NetRole::NONE;
    nkentseu::NkString arg;
    if (state.args.Size() > 1)
        arg = state.args[1];

    if (arg == "--server")
        role = NetRole::SERVER;
    else if (arg == "--client")
        role = NetRole::CLIENT;
    else {
        logger.Error("[APP] : argument attendu --server ou --client");
        return -1;
    }

    if (nkentseu::net::NkSocket::PlatformInit() != nkentseu::net::NkNetResult::NK_NET_OK) {
        logger.Error("[APP] : Echec d'initialisation de la plateforme");
        return -3;
    }

    // -----------------------------------------------------------------------
    // Role serveur : diffuse une ServerInfo toutes les deux secondes
    // pendant dix secondes.
    // -----------------------------------------------------------------------
    if (role == NetRole::SERVER) {
        nkentseu::net::NkDiscovery::ServerInfo info;
        info.addr = nkentseu::net::NkAddress::Any(7777);
        std::strcpy(info.name, "My LAN Server");
        std::strcpy(info.gameMode, "team_deathmatch");
        info.maxPlayers = 16;
        info.hasPassword = false;

        nkentseu::NkClock clock;
        nkentseu::float32 count = 0.f;
        nkentseu::uint64 elapsed = 0;

        while (elapsed < 10000) {
            nkentseu::float32 dt = clock.Tick().delta;
            count += dt;
            elapsed += static_cast<nkentseu::uint64>(dt * 1000.f);

            if (count >= 2.f) {
                count = 0.f;
                nkentseu::net::NkNetResult result =
                    nkentseu::net::NkDiscovery::Broadcast(info);
                if (result != nkentseu::net::NkNetResult::NK_NET_OK)
                    logger.Warn("[APP] : impossible de diffuser les informations du serveur");
                else
                    logger.Info("[APP] : Diffusion des informations du serveur -- nom : {0} -- maxPlayers : {1}",
                                info.name, info.maxPlayers);
            }
            nkentseu::NkChrono::SleepMilliseconds(17);
        }
    }

    // -----------------------------------------------------------------------
    // Role client : ecoute six secondes et affiche chaque serveur trouve.
    // -----------------------------------------------------------------------
    else if (role == NetRole::CLIENT) {
        nkentseu::NkVector<nkentseu::net::NkDiscovery::ServerInfo> servers;

        nkentseu::net::NkNetResult result =
            nkentseu::net::NkDiscovery::Listen(6000, servers);

        if (result != nkentseu::net::NkNetResult::NK_NET_OK) {
            logger.Error("[APP] : echec de l'ecoute");
            return -4;
        }

        logger.Info("[APP] : {0} serveur(s) trouve(s)", servers.Size());

        for (int i = 0; i < static_cast<int>(servers.Size()); ++i) {
            const auto& svr = servers[i];
            logger.Warn("[APP] : serveur #{0} -- adresse : {1} -- nom : {2} -- maxPlayers : {3}",
                        i + 1, svr.addr.ToString(), svr.name, svr.maxPlayers);
        }
    }

    return 0;
}