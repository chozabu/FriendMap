#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QMap>
#include <marble/GeoDataTreeModel.h>
#include <marble/GeoDataDocument.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/GeoPainter.h>
#include <marble/GeoDataStyle.h>

#include "gui/notifyqt.h"
#include "FriendMapSettings.h"
#include "PositionManager.h"
#include "GeoPeer.h"
#include "interface.h"


class DataModel:public QObject
{
public:
    DataModel(GeoDataTreeModel *treeModel):tree_model(treeModel){
        genPeerCache();
        treeModel->addDocument(getDocument());
        myNotifyClient *client = new myNotifyClient(this) ;
        interface::get().mNotify->registerNotifyClient(client) ;
    }
    const GeoPeer* getPeer(const RsPgpId& pgp_id) const;

    const std::list<GeoPeer>& getPeers() const;

    const GeoDataCoordinates getPosition(const GeoPeerLoc& geoloc);

    const QSharedPointer<GeoDataStyle> getStyle(const RsPeerId& peer_id)const;

private:
    void updateAvatar(const std::string& peer_ssl_id);

private:
    class myNotifyClient: public NotifyClient
    {
    public:
        myNotifyClient(DataModel* data_model):data_model(data_model){}
        virtual void notifyPeerHasNewAvatar(std::string peer_id)
        {
            data_model->updateAvatar(peer_id);
        }
    private:
        DataModel* data_model;
    };
    std::list<GeoPeer> geoPeers;
    QMap<RsPgpId, GeoPeer*> peerTable;
    QMap<std::string, GeoPeer*> peer_ssl_id_table;
    QMap<RsPeerId, QSharedPointer<GeoDataStyle>> styleTable;
    PositionManager posman;
    GeoDataTreeModel* tree_model;
    //!
    //!//! \brief geoPeers
    //!
    void genPeerCache();

    GeoDataDocument* getDocument();
};

#endif // DATAMODEL_H
