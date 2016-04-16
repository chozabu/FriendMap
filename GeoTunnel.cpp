#include "GeoTunnel.h"

void GeoTunnel::paint(GeoPainter* painter) const {
    const double speed_bps = tunnel_info.getSpeedBps();
    if (speed_bps > 0) {
        TunnelType type = tunnel_info.getType();
        GeoDataLineString conLine;
        QPen pen;
        pen.setColor(Qt::blue);
        auto calcWidth = [](double speed_bps) {
            Q_ASSERT(speed_bps >= 0);
            constexpr int min_width = 1;
            constexpr int max_width = 80;
            int width = min_width + (speed_bps / 3000);
            if (width > max_width) {
                width = max_width;
            }
            return width;
        };
        pen.setWidth(calcWidth(speed_bps));
        if (type == TunnelType::Download) {
            pen.setColor(Qt::darkGreen);
        } else if (type == TunnelType::Upload) {
            pen.setColor(Qt::darkCyan);
        }
        conLine.append(source);
        conLine.append(dest);

        painter->setPen(pen);
        painter->drawPolyline(conLine);
        float rr = (static_cast<double>(rand()) / (RAND_MAX));
        const GeoDataCoordinates& position = dest.interpolate(source, rr);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawAnnotation(position, QString::fromStdString(tunnel_info.toString()));
    }
}
