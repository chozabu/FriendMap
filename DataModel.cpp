#include "DataModel.h"

const GeoPeer* DataModel::getPeer(const RsPgpId &pgp_id) const {
    return peerTable.value(pgp_id);
}

const std::list<GeoPeer> &DataModel::getPeers() const {
    return geoPeers;
}

const GeoDataCoordinates DataModel::getPosition(const GeoPeerLoc &geoloc){
    return posman.getPosition(geoloc);
}

const QSharedPointer<GeoDataStyle> DataModel::getStyle(const RsPeerId &peer_id) const{
    return styleTable.value(peer_id);
}

void DataModel::updateAvatar(const std::__cxx11::string &peer_ssl_id){
    const RsPgpId& peer_id = interface::get().mPeers->getGPGId(RsPeerId(peer_ssl_id));
    GeoPeer* peer = peerTable.value(peer_id);
    if(peer)
        peer->setAvatar();
    else {
        Q_ASSERT(false);
    }
}

void DataModel::genPeerCache(){

    std::list<RsPgpId> gpg_ids;
    RsPeers* rsPeers = interface::get().mPeers;
    rsPeers->getGPGAcceptedList(gpg_ids);
    gpg_ids.push_back(rsPeers->getGPGId(rsPeers->getOwnId()));

    geoPeers.clear();
    peerTable.clear();

    foreach(const RsPgpId& gpg_id, gpg_ids){
        geoPeers.emplace_back(gpg_id);
        GeoPeer* gp = &geoPeers.back();
        peerTable.insert(gpg_id, gp);
    }
}

GeoDataDocument *DataModel::getDocument()
{
    GeoDataDocument* document = new GeoDataDocument;
    foreach(const GeoPeer& geoPeer, geoPeers){
        foreach(const GeoPeerLoc& geoPeerLoc, geoPeer.getLocations()){
            QSharedPointer<GeoDataStyle> style(new GeoDataStyle);
            if(geoPeerLoc.geoLocSuccess()){
                GeoDataPlacemark* placemark = new GeoDataPlacemark( geoPeerLoc.getName()+"@"+geoPeerLoc.getLocation() );
                GeoDataCoordinates coord = posman.getPosition(geoPeerLoc);
                placemark->setCoordinate(coord);
                placemark->setCountryCode(geoPeerLoc.getCountryCode());
                placemark->setDescription(geoPeerLoc.toString());



                if(true){
                    GeoDataIconStyle iconStyle;
                    iconStyle.setIcon( geoPeer.getAvatar().toImage() );
                    iconStyle.setScale(0.3);
                    style->setIconStyle(iconStyle);
                }
                GeoDataLabelStyle online;
                online.setColor(Qt::darkGreen);
                if(geoPeerLoc.isOnline()){
                    style->setLabelStyle(online);
                }
                placemark->setStyle(style);
                document->append( placemark );
            }
            styleTable.insert(geoPeerLoc.getSslId(), style);
        }
    }
    return document;
}
