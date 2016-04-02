#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H

#include <math.h>
#include <QMap>
#include <marble/GeoDataCoordinates.h>
#include "GeoPeer.h"

#define TAU 6.28318530718

class Offset{
public:
    Offset();

    Offset(double angle, double distance);

    Offset getIncreased();

    GeoDataCoordinates offsetCoord(const GeoDataCoordinates& coord) const {
        qreal lon, lat;
        coord.geoCoordinates(lon, lat, GeoDataCoordinates::Degree);
        GeoDataCoordinates new_coord(lon+cos(angle)*distance, lat+sin(angle)*distance, coord.altitude(), GeoDataCoordinates::Degree);
        return new_coord;
    }

private:
    static constexpr double angular_step = TAU/10.0;
    double distance;
    double angle;
};

class PositionManager
{
public:
    PositionManager();
    const GeoDataCoordinates getPosition(const GeoPeerLoc& geoloc){
        const RsPeerId ssl_id = geoloc.getSslId();
        const GeoDataCoordinates& gcoord = geoloc.getCoordinates();
        qreal lon, lat;
        gcoord.geoCoordinates(lon, lat);
        std::pair<double,double> coord(roundCoord(lon), roundCoord(lat));
        if(!map.contains(ssl_id)){
            if(!coord_map.contains(coord)){
                Offset offset;
                coord_map.insert(coord, offset);
            }
            Offset off = coord_map[coord];
            map.insert(ssl_id, off.offsetCoord(gcoord));
            coord_map.insert(coord, off.getIncreased());
        }
        return map.value(ssl_id);
    }
private:
    QMap<RsPeerId,GeoDataCoordinates> map;
    QMap<std::pair<double,double>,Offset> coord_map;
    double roundCoord(double x){
        int precision = 1000;
        return roundf(x*precision)/precision;
    }

};

#endif // POSITIONMANAGER_H
