#include "DataModel.h"

DataModel::DataModel(GeoDataTreeModel* treeModel) {
    genPeerCache();
    treeModel->addDocument(getDocument());
    notify_client = new myNotifyClient(this);
    interface::get().mNotify->registerNotifyClient(notify_client);
}

DataModel::~DataModel() {
    interface::get().mNotify->unregisterNotifyClient(notify_client);
    delete notify_client;
}

const GeoPeer& DataModel::getPeer(const RsPgpId& pgp_id) const {
    GeoPeer* peer = peerTable.value(pgp_id);
    if (peer != nullptr) {
        return *peer;
    }
    return GeoPeer::NULLPEER;
}

const QList<GeoPeer*> DataModel::getPeers() const {
    return peerTable.values();
}

const GeoDataCoordinates DataModel::getPosition(const GeoPeerLoc& geoloc) {
    return PositionManager::instance().getPosition(geoloc);
}

const GeoPeerLoc& DataModel::getLocationBySslID(const RsPeerId& peer_ssl_id) const {
    Q_ASSERT(!peer_ssl_id.isNull());
    QSharedPointer<const GeoPeerLoc> loc = peer_ssl_id_table.value(peer_ssl_id);
    return *loc;
}

const RsPeerId DataModel::getLocationByName(const std::string& name) const {
    return name2loc_table.value(name)->getSslId();
}

std::list<const GeoPeerLoc*> DataModel::getLocations(const GeoPeer& peer) const {
    std::list<const GeoPeerLoc*> list;
    foreach (auto ssl_id, peer.getAssociatedSSLIds())
        list.push_back(&getLocationBySslID(ssl_id));
    return list;
}

GeoDataCoordinates DataModel::getMainLocation(const GeoPeer& peer) const {
    Q_ASSERT(!peer.isNull());
    GeoDataCoordinates peer_location = GeoPeerLoc::DEFAULT;
    foreach (const GeoPeerLoc* const loc, getLocations(peer)) {
        if (loc->getExactCoordinates() != GeoPeerLoc::DEFAULT) {
            peer_location = loc->coordinate();
        }
    }
    if (peer_location == GeoPeerLoc::DEFAULT && getLocations(peer).size() > 0) {
        peer_location = getLocations(peer).front()->coordinate();
    }
    return peer_location;
}

void DataModel::updateAvatar(const std::string& peer_ssl_id) {
    const RsPgpId& peer_id = interface::get().mPeers->getGPGId(RsPeerId(peer_ssl_id));
    GeoPeer* peer = peerTable.value(peer_id);
    if (peer != nullptr) {
        peer->setAvatar();
        foreach (auto ssl_id, peer->getAssociatedSSLIds()) {
            QSharedPointer<GeoPeerLoc> loc = peer_ssl_id_table.value(RsPeerId(ssl_id));
            if (!loc.isNull()) {
                loc->updateAvatar();
            }
        }
    }
}

void DataModel::updatePeerStatus(const std::string& peer_ssl_id, uint32_t /*unused*/) {
    const RsPeerId& peer_id = (RsPeerId(peer_ssl_id));
    QSharedPointer<GeoPeerLoc> loc = peer_ssl_id_table.value(peer_id);
    if (!loc.isNull()) {
        loc->checkOnline();
    }
}

void DataModel::genPeerCache() {
    std::list<RsPgpId> gpg_ids;
    RsPeers* rsPeers = interface::get().mPeers;
    rsPeers->getGPGAcceptedList(gpg_ids);
    //rsPeers->getGPGAllList(gpg_ids);
    geoPeers.clear();
    peerTable.clear();
    foreach (const RsPgpId& gpg_id, gpg_ids) {
        addPeer(gpg_id);
    }
    const RsPgpId own_gpg_id = rsPeers->getGPGOwnId();
    addPeer(own_gpg_id);
}

void DataModel::addPeer(const RsPgpId& gpg_id) {
    geoPeers.emplace_back(gpg_id);
    GeoPeer* gp = &geoPeers.back();
    if (gp->isSelf()) {
        GeoPeerLoc own_loc(rsPeers->getOwnId());
    }
    peerTable.insert(gpg_id, gp);
    foreach (auto ssl_id, gp->getAssociatedSSLIds()) {
        auto gplp = new GeoPeerLoc(ssl_id);
        QSharedPointer<GeoPeerLoc> qgplp(gplp);
        peer_ssl_id_table.insert(ssl_id, qgplp);
        name2loc_table.insert(gp->getName() + " (" + gplp->getLocation().toStdString() + ")", qgplp);
    }
}

GeoDataDocument* DataModel::getDocument() {
    auto document = new GeoDataDocument;
    foreach (const GeoPeer& geoPeer, geoPeers) {
        foreach (RsPeerId ssl_id, geoPeer.getAssociatedSSLIds()) {
            GeoPeerLoc* placemark = const_cast<GeoPeerLoc*>(&getLocationBySslID(ssl_id));
            document->append(placemark);
        }
    }
    return document;
}
