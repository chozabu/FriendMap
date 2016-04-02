#include "GeoPeer.h"

GeoPeerLoc::GeoPeerLoc(const RsPeerId &ssl_id, GeoIP *geoip, RsPeers *rsPeers){
    rsPeers->getPeerDetails(ssl_id, peer_ssl_details);
    GeoIPRecord* r = GeoIP_record_by_name(geoip, peer_ssl_details.extAddr.c_str());
    if(r){
        coord = GeoDataCoordinates(r->longitude, r->latitude, 0.0, GeoDataCoordinates::Degree);
        city = QString::fromUtf8(r->city);
        country_name = QString::fromUtf8(r->country_name);
        country_code = QString::fromUtf8(r->country_code);
        region = QString::fromUtf8(r->region);
        geolocation_successful = true;
        GeoIPRecord_delete(r);
    } else {
        coord = GeoDataCoordinates(0, 90, 0, GeoDataCoordinates::Degree);
        geolocation_successful = false;
    }
}

bool GeoPeerLoc::geoLocSuccess() const {
    return geolocation_successful;
}

QString GeoPeerLoc::getName() const {
    return QString::fromStdString(peer_ssl_details.name);
}

QString GeoPeerLoc::getLocation() const {
    return QString::fromStdString(peer_ssl_details.location);
}

QString GeoPeerLoc::getIP() const {
    return QString::fromStdString(peer_ssl_details.extAddr);
}

bool GeoPeerLoc::isOnline() const {
    return rsPeers->isOnline(peer_ssl_details.id);
}

const GeoDataCoordinates &GeoPeerLoc::getCoordinates() const {
    return coord;
}

QString GeoPeerLoc::getCity() const {
    return city;
}

QString GeoPeerLoc::getCountryCode() const {
    return country_code;
}

QString GeoPeerLoc::getCountryName() const {
    return country_name;
}

QString GeoPeerLoc::getRegion() const {
    return region;
}

const RsPeerId GeoPeerLoc::getSslId() const {
    return peer_ssl_details.id;
}

QString GeoPeerLoc::toString() const {
    QString html = "<table>";
    html += "<tr><td>Name</td><td>"+getName()+"</td></tr>";
    html += "<tr><td>Location</td><td>"+getLocation()+"</td></tr>";
    html += "<tr><td>IP</td><td>"+getIP()+"</td></tr>";
    html += "<tr><td>Country</td><td>"+getCountryName()+"</td></tr>";
    if(getCountryCode()=="US")
        html += "<tr><td>State</td><td>"+getRegion()+"</td></tr>";
    if(!getCity().isEmpty())
        html += "<tr><td>City</td><td>"+getCity()+"</td></tr>";
    html += "</table>";
    return html;
}

GeoPeer::GeoPeer(){/*To satisfy container datastructures.*/}

GeoPeer::GeoPeer(const RsPgpId &gpg_id, RsPeers *rsPeers, GeoIP *geoip){
    rsPeers->getGPGDetails(gpg_id, peer_details);
    setLocations(gpg_id, rsPeers, geoip);
    setAvatar();
}

const RsPgpId &GeoPeer::getGpgId() const {
    return (peer_details.gpg_id);
}

const QList<GeoPeerLoc> &GeoPeer::getLocations() const {
    return locations;
}

const QPixmap& GeoPeer::getAvatar()  {
    //setAvatar();
    return avatar;
}

const QPixmap &GeoPeer::getAvatar() const {
    return avatar;
}

const QList<RsPgpId> GeoPeer::getConnectionsList() const {
    std::list<RsPgpId> friendList;
    interface::get().mDisc->getDiscPgpFriends((getGpgId()), friendList);
    QList<RsPgpId> connectionsList;
    foreach(const RsPgpId& gpg_id, friendList){
        connectionsList.push_back(gpg_id);
    }
    return connectionsList;
}

void GeoPeer::setAvatar(){
    AvatarDefs::getAvatarFromGpgId(getGpgId(), avatar);
    //avatar = avatar.scaledToWidth(22);
}

void GeoPeer::setLocations(const RsPgpId &gpg_id, RsPeers *rsPeers, GeoIP *geoip){
    std::list<RsPeerId> ssl_ids;
    rsPeers->getAssociatedSSLIds(gpg_id, ssl_ids);
    foreach(const RsPeerId& ssl_id, ssl_ids){
        RsPeerDetails peer_ssl_details;
        rsPeers->getPeerDetails(ssl_id, peer_ssl_details);
        if(peer_ssl_details.extAddr.compare("0.0.0.0")){
            //std::cout<<peer_ssl_details.extAddr<<"\n";

            GeoPeerLoc sLocation(ssl_id, geoip, rsPeers);
            if(sLocation.geoLocSuccess())
                locations.push_back(sLocation);

        }

    }
}
