#ifndef GEOTUNNEL_H
#define GEOTUNNEL_H

#include <marble/GeoDataPlacemark.h>
#include "PositionManager.h"
#include "TurtleTunnelInfo.h"
#include "paintable.h"

class GeoTunnel : public Marble::GeoDataPlacemark, public Paintable {
   public:
    explicit GeoTunnel(const TurtleTunnelInfo& tunnel_info) : tunnel_info(tunnel_info) {
        this->setName(QString::fromStdString(tunnel_info.getIdString()));
        source = PositionManager::instance().getPosition(tunnel_info.getSourceID());
        dest = PositionManager::instance().getPosition(tunnel_info.getDestinationID());
        this->setCoordinate(source.interpolate(dest, 0.5));
        update(tunnel_info);
    }
    void update(const TurtleTunnelInfo& tunnel_info) {
        this->tunnel_info = tunnel_info;
        this->setDescription(QString::fromStdString(tunnel_info.toString()));
    }

    virtual void paint(GeoPainter* painter) const override;

   private:
    TurtleTunnelInfo tunnel_info;
    GeoDataCoordinates source, dest;
};

#endif  // GEOTUNNEL_H
