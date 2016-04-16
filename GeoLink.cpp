#include "GeoLink.h"

void GeoLink::paint(GeoPainter* painter) const {
    if (!geoPeer.isSelf() && data_model->getMainLocation(geoPeer) != GeoPeerLoc::DEFAULT) {
        painter->setPen(Qt::yellow);
        foreach (const RsPgpId& gpg_id, geoPeer.getConnectionsList()) {
            const GeoPeer& other = data_model->getPeer(gpg_id);
            if (!other.isNull() && !other.isSelf() && other.getAssociatedSSLIds().size() > 0 && data_model->getMainLocation(other) != GeoPeerLoc::DEFAULT) {
                GeoDataLineString conLine;
                conLine.append(data_model->getMainLocation(geoPeer));
                conLine.append(data_model->getMainLocation(other));
                painter->drawPolyline(conLine);
            }
        }
    }
}
