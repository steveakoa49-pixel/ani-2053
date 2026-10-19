#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKNetwork/NKNetwork.h"

#include <cstring>

enum class NetRole {
    NONE,
    SERVER,
    CLIENT
};

// ---------------------------------------------------------------------------
// Un seul programme, deux roles, choisis par un argument :
//   parle.exe --server
//   parle.exe --client <adresse-du-serveur>
// ---------------------------------------------------------------------------
int nkmain(const nkentseu::NkEntryState& state) {
    NetRole role = NetRole::NONE;
    nkentseu::NkString arg;
    nkentseu::NkString ip;
    nkentseu::uint16 port = 7777;

    if (state.args.Size() > 1)
        arg = state.args[1];
    if (state.args.Size() > 2)
        ip = state.args[2];

    logger.Warn("[APP] ARGUMENT : {0}, ip : {1}", arg.CStr(), ip.CStr());

    if (arg == "--server") {
        role = NetRole::SERVER;
    }
    else if (arg == "--client") {
        role = NetRole::CLIENT;
        if (ip.Empty()) {
            logger.Error("[APP] : Omission de l'IP du serveur !");
            return -2;
        }
    }
    else {
        logger.Error("[APP] : argument attendu --server ou --client <ip>");
        return -1;
    }

    // Initialisation de la plateforme reseau.
    if (nkentseu::net::NkSocket::PlatformInit() != nkentseu::net::NkNetResult::NK_NET_OK) {
        logger.Error("[APP] : Echec d'initialisation de la plateforme");
        return -3;
    }

    nkentseu::NkConnectionManager manager;

    // -----------------------------------------------------------------------
    // Serveur : demarre, attend un client, draine a chaque tour et affiche
    // chaque message recu avec l'identifiant de son expediteur (msg.from).
    // -----------------------------------------------------------------------
    if (role == NetRole::SERVER) {
        manager.onPeerConnected = [](nkentseu::net::NkPeerId peer) {
            logger.Warn("[APP] : Client connecte avec succes -- ID pair : {0}", peer.value);
        };

        nkentseu::net::NkNetResult result = manager.StartServer(port, 8);
        if (result != nkentseu::net::NkNetResult::NK_NET_OK) {
            logger.Error("[APP] : Echec du demarrage du serveur");
            return -4;
        }
        logger.Info("[APP] : Serveur demarre sur le port {0}", port);

        // On attend qu'au moins un client soit connecte.
        nkentseu::uint64 waited = 0;
        while (manager.ConnectedPeerCount() < 1) {
            waited++;
            if (waited >= 300000000u) {
                logger.Info("[APP] : RECHERCHE DU CLIENT");
                waited = 0;
            }
        }

        // Boucle de collecte : DrainAll a chaque tour.
        nkentseu::uint64 loops = 0;
        while (true) {
            nkentseu::NkVector<nkentseu::net::NkReceiveMsg> msgs;
            msgs.Clear();
            manager.DrainAll(msgs);

            for (int i = 0; i < static_cast<int>(msgs.Size()); ++i) {
                const auto& msg = msgs[i];
                nkentseu::NkString clientMsg{reinterpret_cast<const char*>(msg.data), msg.size};
                logger.Warn("[Serveur] : \"{0}\" -- expediteur : {1}",
                            clientMsg.CStr(), msg.from.value);
            }

            // On s'arrete apres avoir recu au moins un message.
            if (msgs.Size() > 0) {
                logger.Info("[APP] : Message recu, arret du serveur");
                break;
            }

            loops++;
        }
    }

    // -----------------------------------------------------------------------
    // Client : se connecte, attend l'etablissement, envoie un court message
    // au serveur via SendTo, et affiche l'identifiant du pair a la connexion.
    // -----------------------------------------------------------------------
    else if (role == NetRole::CLIENT) {
        manager.onPeerConnected = [](nkentseu::net::NkPeerId peer) {
            logger.Warn("[APP] : Serveur connecte avec succes -- ID pair : {0}", peer.value);
        };

        nkentseu::net::NkAddress address(ip.CStr(), port);
        if (!address.IsValid()) {
            logger.Error("[APP] : Adresse invalide");
            return -5;
        }

        const auto result = manager.Connect(address);
        if (result != nkentseu::net::NkNetResult::NK_NET_OK) {
            logger.Error("[APP] : Erreur de connexion du client au serveur");
            return -6;
        }
        logger.Info("[APP] : Connexion initiee vers {0}:{1}", ip.CStr(), port);

        // La connexion se fait dans un fil du moteur : on laisse le temps
        // au client d'etre connecte avant d'envoyer.
        nkentseu::uint64 waited = 0;
        while (manager.ConnectedPeerCount() < 1) {
            waited++;
            if (waited >= 300000000u) {
                logger.Info("[APP] : RECHERCHE DU SERVEUR");
                waited = 0;
            }
        }

        // Petit temps supplementaire pour laisser le handshake se terminer.
        for (volatile nkentseu::uint64 i = 0; i < 10000000u; ++i) {}

        // Envoi d'un court message texte au serveur.
        nkentseu::NkString msg = "Bonjour depuis le client.";
        nkentseu::NkVector<nkentseu::uint8> buffer(msg.Size());
        std::memcpy(buffer.Data(), msg.Data(), msg.Size());

        nkentseu::net::NkNetResult r = manager.SendTo(
            nkentseu::net::NkPeerId::Server(),
            buffer.Data(),
            static_cast<nkentseu::uint32>(buffer.Size()));

        if (r != nkentseu::net::NkNetResult::NK_NET_OK)
            logger.Warn("[APP] : Erreur d'envoi du message sur le fil");
        else
            logger.Warn("[APP] : Message envoye");

        // Laisse le temps a l'envoi de partir avant de quitter.
        for (volatile nkentseu::uint64 i = 0; i < 30000000u; ++i) {}
    }

    return 0;
}