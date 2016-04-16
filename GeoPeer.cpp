#include "GeoPeer.h"
#include "PositionManager.h"

const GeoPeer GeoPeer::NULLPEER;
bool success;
const GeoDataCoordinates GeoPeerLoc::DEFAULT = GeoDataCoordinates::fromString("45° 11' 36,5\"W,  29° 34' 15,9\"N", success);
//ASSERT(success);

GeoPeerLoc::GeoPeerLoc(const RsPeerId& ssl_id) {
    Q_ASSERT(!ssl_id.isNull());
    interface::get().mPeers->getPeerDetails(ssl_id, peer_ssl_details);
    GeoIPRecord* r = GeoIP_record_by_name(interface::getGeoIP(), peer_ssl_details.extAddr.c_str());
    setName(getName() + "@" + getLocation());
    if (r != nullptr) {
        coord = GeoDataCoordinates(r->longitude, r->latitude, 0.0, GeoDataCoordinates::Degree);
        city = QString::fromUtf8(r->city);
        country_name = QString::fromUtf8(r->country_name);
        country_code = QString::fromUtf8(r->country_code);
        setCountryCode(country_code);
        region = QString::fromUtf8(r->region);
        GeoIPRecord_delete(r);
    } else {
        coord = DEFAULT;
    }
    setCoordinate(PositionManager::instance().getPosition(*this));
    updateAvatar();
    checkOnline();
    setDescription(toString());
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

const GeoDataCoordinates& GeoPeerLoc::getExactCoordinates() const {
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
    html += "<tr><td>Name</td><td>" + getName() + "</td></tr>";
    html += "<tr><td>Location</td><td>" + getLocation() + "</td></tr>";
    html += "<tr><td>IP</td><td>" + getIP() + "</td></tr>";
    html += "<tr><td>Country</td><td>" + getCountryName() + "</td></tr>";
    if (getCountryCode() == "US") {
        html += "<tr><td>State</td><td>" + getRegion() + "</td></tr>";
    }
    if (!getCity().isEmpty()) {
        html += "<tr><td>City</td><td>" + getCity() + "</td></tr>";
    }
    html += "</table>";
    return html;
}

void GeoPeerLoc::checkOnline() {
    this->is_online = interface::get().mPeers->isOnline(getSslId()) || getSslId() == interface::get().mPeers->getOwnId();
    QSharedPointer<GeoDataStyle> style(new GeoDataStyle(*this->style()));
    if (is_online) {
        GeoDataLabelStyle online;
        online.setColor(Qt::darkGreen);
        style->setLabelStyle(online);
    } else {
        GeoDataLabelStyle offline;
        offline.setColor(Qt::darkRed);
        style->setLabelStyle(offline);
    }
    setStyle(style);
}

void GeoPeerLoc::updateAvatar() {
    GeoDataIconStyle iconStyle;
    AvatarDefs::getAvatarFromGpgId(peer_ssl_details.gpg_id, avatar);
    iconStyle.setIcon(avatar.toImage());
    iconStyle.setScale(0.3);
    QSharedPointer<GeoDataStyle> style(new GeoDataStyle(*this->style()));
    style->setIconStyle(iconStyle);
    setStyle(style);
}

void GeoPeerLoc::paint(GeoPainter* painter) const {
    const GeoDataCoordinates offCoord = PositionManager::instance().getPosition(*this);
    if (is_online) {
        painter->setPen(Qt::darkGreen);
    } else {
        painter->setPen(Qt::red);
    }

    GeoDataLineString cLine;
    cLine.append(offCoord);
    cLine.append(getExactCoordinates());
    painter->drawPolyline(cLine);
}

GeoPeer::GeoPeer(const RsPgpId& gpg_id) {
    interface::get().mPeers->getGPGDetails(gpg_id, peer_details);
    setAvatar();
    is_null = false;
}

const RsPgpId& GeoPeer::getGpgId() const {
    return (peer_details.gpg_id);
}

void GeoPeer::setAvatar() {
    AvatarDefs::getAvatarFromGpgId(getGpgId(), avatar);
}

bool GeoPeer::isSelf() const {
    const RsPgpId& own_pgp_id = interface::get().mPeers->getGPGOwnId();
    return own_pgp_id == getGpgId();
}

std::list<RsPeerId> GeoPeer::getAssociatedSSLIds() const {
    std::list<RsPeerId> ids;
    interface::get().mPeers->getAssociatedSSLIds(getGpgId(), ids);
    if (isSelf()) {
        ids.push_back(interface::get().mPeers->getOwnId());
    }
    return ids;
}

std::list<RsPgpId> GeoPeer::getConnectionsList() const {
    std::list<RsPgpId> friend_list;
    interface::get().mDisc->getDiscPgpFriends((getGpgId()), friend_list);
    return friend_list;
}
