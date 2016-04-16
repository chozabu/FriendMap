#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H

#include <marble/GeoDataCoordinates.h>
#include <math.h>
#include <retroshare/rsdisc.h>
#include <retroshare/rsplugin.h>
#include <QMap>

#define TAU 6.28318530718

using namespace Marble;

class GeoPeerLoc;

class Offset {
   public:
    Offset();

    Offset(double angle, double distance);

    Offset getIncreased();

    GeoDataCoordinates offsetCoord(const GeoDataCoordinates& coord) const;

   private:
    static constexpr double angular_step = TAU / 10.0;
    double distance;
    double angle;
};

class PositionManager {
   public:
    const GeoDataCoordinates getPosition(const GeoPeerLoc& geoloc);

    /*!
     * \brief getPosition Looks for the position corresponding to a ssl_id. Only call this if after ssl_id was inserted into the PositionManager.
     * \param ssl_id
     * \return Pointer to an GeoDataCoordinates object.
     */
    GeoDataCoordinates getPosition(const RsPeerId ssl_id) {
        return map.value(ssl_id);
    }

    static PositionManager& instance() {
        static PositionManager instance;
        return instance;
    }

   private:
    PositionManager();
    PositionManager(const PositionManager&);
    PositionManager& operator=(const PositionManager&);
    QMap<RsPeerId, GeoDataCoordinates> map;
    QMap<std::pair<double, double>, Offset> coord_map;
    double roundCoord(double x) {
        int precision = 1000;
        return roundf(x * precision) / precision;
    }
};

#endif  // POSITIONMANAGER_H
