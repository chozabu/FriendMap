#ifndef GEOLINK_H
#define GEOLINK_H

#include "DataModel.h"
#include "GeoPeer.h"
#include "paintable.h"

class GeoLink : public Paintable {
   public:
    GeoLink(const GeoPeer& peer, DataModel* data_model) : geoPeer(peer), data_model(data_model) {
    }
    virtual void paint(GeoPainter* painter) const override;

   private:
    const GeoPeer& geoPeer;
    DataModel* data_model;
};

#endif  // GEOLINK_H
