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

class PaintLayer : public LayerInterface, public QObject
{
public:
    PaintLayer(RsPeers* peers, RsDisc* disc, const FriendMapSettings* settings);
    ~PaintLayer();
    // Implemented from LayerInterface
    virtual QStringList renderPosition() const;

    // Implemented from LayerInterface
    virtual bool render( GeoPainter *painter, ViewportParams *viewport,
	                     const QString& renderPos = "NONE", GeoSceneLayer * layer = 0 );
public slots:
	void genPeerCache();
private:
	const FriendMapSettings* mSettings;
	bool showingLinks;
	RsPeers* rsPeers;
	RsDisc* rsDisc;
    GeoIP* geoip;
};

#endif // PAINTLAYER_H
