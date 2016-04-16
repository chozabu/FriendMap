#ifndef GEOPEER_H
#define GEOPEER_H

#include <GeoIP.h>
#include <GeoIPCity.h>
#include <marble/GeoDataCoordinates.h>
#include <marble/GeoDataDocument.h>
#include <QPixmap>
#include "PositionManager.h"
#include "gui/common/AvatarDefs.h"
#include "interface.h"
#include "paintable.h"

using namespace Marble;

//!
//! \brief The GeoPeerLoc class
//!
class GeoPeerLoc : public GeoDataPlacemark, public Paintable {
   public:
    static const GeoDataCoordinates DEFAULT;
    explicit GeoPeerLoc(const RsPeerId& ssl_id);
    QString getName() const;
    QString getLocation() const;
    QString getIP() const;
    bool isOnline() const;
    /*!
     * \brief getExactCoordinates Return the exact coordinates without offset. Use the inherited coordinate() for the placemarks position on the map.
     * \return exact coordinates like without offset.
     */
    const GeoDataCoordinates& getExactCoordinates() const;
    QString getCity() const;
    QString getCountryCode() const;
    QString getCountryName() const;
    QString getRegion() const;
    const RsPeerId getSslId() const;
    QString toString() const;
    void checkOnline();
    void updateAvatar();

    bool isOwn() const;

    virtual void paint(GeoPainter* painter) const override;

   private:
    RsPeerDetails peer_ssl_details;
    QString city, country_name, country_code, region;
    GeoDataCoordinates coord;
    QPixmap avatar;
    bool is_online;
};

//!
//! \brief The GeoPeer class
//!
class GeoPeer {
   public:
    static const GeoPeer NULLPEER;
    GeoPeer() : is_null(true) {}
    explicit GeoPeer(const RsPgpId& gpg_id);

    const RsPgpId& getGpgId() const;
    const std::string& getName() const {
        return peer_details.name;
    }

    bool hasOwnSign() const {
        return peer_details.ownsign;
    }

    void setAvatar();
    bool isNull() const {
        return is_null;
    }
    bool isSelf() const;
    std::list<RsPeerId> getAssociatedSSLIds() const;
    std::list<RsPgpId> getConnectionsList() const;

   private:
    RsPeerDetails peer_details;
    QPixmap avatar;
    bool is_null;
};

#endif  // GEOPEER_H
