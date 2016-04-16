#ifndef PAINTABLE_H
#define PAINTABLE_H

#include <marble/GeoDataCoordinates.h>
#include <marble/GeoDataLineString.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/GeoPainter.h>

using namespace Marble;

class Paintable {
   public:
    virtual void paint(GeoPainter* painter) const = 0;
};

#endif  // PAINTABLE_H
