#ifndef PAINTLAYER_H
#define PAINTLAYER_H

#include <marble/MarbleWidget.h>
#include <marble/MarbleMap.h>
#include <marble/MarbleModel.h>
#include <marble/GeoPainter.h>
#include <marble/LayerInterface.h>

#include <GeoIP.h>
#include <GeoIPCity.h>

#include <retroshare/rsplugin.h>
#include "FriendMapSettings.h"

using namespace Marble;

class PaintLayer : public LayerInterface
{
public:
    PaintLayer(RsPeers* peers, const FriendMapSettings* settings);
    ~PaintLayer();
    // Implemented from LayerInterface
    virtual QStringList renderPosition() const;

    // Implemented from LayerInterface
    virtual bool render( GeoPainter *painter, ViewportParams *viewport,
                         const QString& renderPos = "NONE", GeoSceneLayer * layer = 0 );
private:
    RsPeers* rsPeers;
    GeoIP* geoip;
};

#endif // PAINTLAYER_H
