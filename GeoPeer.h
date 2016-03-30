#ifndef GEOPEER_H
#define GEOPEER_H

#include <retroshare/rsplugin.h>
#include <retroshare/rsdisc.h>
#include <QPixmap>
#include <marble/GeoDataCoordinates.h>
#include <marble/GeoDataCoordinates.h>
#include <GeoIP.h>
#include <GeoIPCity.h>
#include "gui/common/AvatarDefs.h"
#include "interface.h"

using namespace Marble;

//!
//! \brief The GeoPeerLoc class
//!
class GeoPeerLoc{
public:
    GeoPeerLoc(const RsPeerId& ssl_id, GeoIP* geoip, RsPeers* rsPeers);
    bool geoLocSuccess() const;
    QString getName() const;
    QString getLocation() const;
    QString getIP() const;
    bool isOnline() const;
    const GeoDataCoordinates& getCoordinates() const;
    QString getCity() const;
    QString getCountryCode() const;
    QString getCountryName() const;
    QString getRegion() const;
    const RsPeerId getSslId() const;
    QString toString() const;

private:
    RsPeerDetails peer_ssl_details;
    QString city, country_name, country_code, region;
    GeoDataCoordinates coord;
    bool geolocation_successful;
};

//!
//! \brief The GeoPeer class
//!
class GeoPeer{
public:
    GeoPeer();
    GeoPeer(const RsPgpId &gpg_id):GeoPeer(gpg_id, interface::get().mPeers, interface::getGeoIP()){}

    const RsPgpId& getGpgId() const;
    const QList<GeoPeerLoc>& getLocations() const;
    const QPixmap &getAvatar();
    const QPixmap &getAvatar() const;
    const QList<RsPgpId> getConnectionsList() const;
    void setAvatar();

private:
    GeoPeer(const RsPgpId& gpg_id, RsPeers* rsPeers, GeoIP* geoip);
    RsPeerDetails peer_details;
    QList<GeoPeerLoc> locations;
    QPixmap avatar;
    void setLocations(const RsPgpId& gpg_id, RsPeers* rsPeers, GeoIP* geoip);
};

#endif // GEOPEER_H
