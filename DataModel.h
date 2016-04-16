#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <marble/GeoDataDocument.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/GeoDataStyle.h>
#include <marble/GeoDataTreeModel.h>
#include <marble/GeoPainter.h>
#include <QMap>

#include "FriendMapSettings.h"
#include "GeoPeer.h"
#include "PositionManager.h"
#include "gui/notifyqt.h"
#include "interface.h"

class DataModel : public QObject {
   public:
    explicit DataModel(GeoDataTreeModel* treeModel);
    ~DataModel();

    const GeoPeer& getPeer(const RsPgpId& pgp_id) const;
    const QList<GeoPeer*> getPeers() const;
    const GeoDataCoordinates getPosition(const GeoPeerLoc& geoloc);
    const GeoPeerLoc& getLocationBySslID(const RsPeerId& peer_ssl_id) const;
    /*!
     * \brief getLocationByName
     * \param name Name in the form "PeerName (LocationName)"
     * \return ssl id
     */
    const RsPeerId getLocationByName(const std::string& name) const;

    std::list<const GeoPeerLoc*> getLocations(const GeoPeer& peer) const;

    GeoDataCoordinates getMainLocation(const GeoPeer& peer) const;

   private:
    void updateAvatar(const std::string& peer_ssl_id);
    void updatePeerStatus(const std::string& peer_ssl_id, uint32_t /*status*/);

    class myNotifyClient : public NotifyClient {
       public:
        explicit myNotifyClient(DataModel* data_model) : data_model(data_model) {}
        virtual void notifyPeerHasNewAvatar(std::string peer_id) {
            data_model->updateAvatar(peer_id);
        }
        virtual void notifyPeerStatusChanged(const std::string& peer_id, uint32_t status) {
            data_model->updatePeerStatus(peer_id, status);
        }

       private:
        DataModel* data_model;
    };
    std::list<GeoPeer> geoPeers;
    QMap<RsPgpId, GeoPeer*> peerTable;
    QMap<RsPeerId, QSharedPointer<GeoPeerLoc> > peer_ssl_id_table;
    QMap<std::string, QSharedPointer<const GeoPeerLoc> > name2loc_table;
    void genPeerCache();
    void addPeer(const RsPgpId& gpg_id);
    myNotifyClient* notify_client;
    GeoDataDocument* getDocument();
};

#endif  // DATAMODEL_H
