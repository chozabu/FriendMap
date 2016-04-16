#include "PositionManager.h"
#include "GeoPeer.h"

const GeoDataCoordinates PositionManager::getPosition(const GeoPeerLoc& geoloc) {
    const RsPeerId ssl_id = geoloc.getSslId();
    const GeoDataCoordinates& gcoord = geoloc.getExactCoordinates();
    qreal lon, lat;
    gcoord.geoCoordinates(lon, lat);
    std::pair<double, double> coord(roundCoord(lon), roundCoord(lat));
    if (!map.contains(ssl_id)) {
        if (!coord_map.contains(coord)) {
            Offset offset;
            coord_map.insert(coord, offset);
        }
        Offset off = coord_map[coord];
        map.insert(ssl_id, off.offsetCoord(gcoord));
        coord_map.insert(coord, off.getIncreased());
    }
    return map.value(ssl_id);
}

PositionManager::PositionManager() {}

Offset::Offset() {
    distance = 0.3;
    angle = 0;
}

Offset::Offset(double angle, double distance) {
    this->distance = distance;
    this->angle = angle;
}

Offset Offset::getIncreased() {
    double new_distance = distance;
    double new_angle = angle + angular_step;
    if (TAU - new_angle < 0.0001) {
        new_distance += 0.3;
        new_angle = 0;
    }
    Offset increased(new_angle, new_distance);
    return increased;
}

GeoDataCoordinates Offset::offsetCoord(const GeoDataCoordinates& coord) const {
    qreal lon, lat;
    coord.geoCoordinates(lon, lat, GeoDataCoordinates::Degree);
    GeoDataCoordinates new_coord(lon + cos(angle) * distance, lat + sin(angle) * distance, coord.altitude(), GeoDataCoordinates::Degree);
    return new_coord;
}
