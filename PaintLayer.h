/*!
 * @file PaintLayer.h
 * @author Nyfor, RetroShare Team
 * 
 * Copyright (C) 2014 - Nyfor, RetroShare Team
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

#ifndef PAINTLAYER_H
#define PAINTLAYER_H

#include <marble/LayerInterface.h>
#include <marble/GeoDataTreeModel.h>
#include <marble/GeoDataDocument.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/GeoPainter.h>
#include <GeoIP.h>

#include "FriendMapSettings.h"
#include "interface.h"
#include "DataModel.h"

using namespace Marble;

/**
 * @brief Define class PaintLayer
 */
class PaintLayer : public LayerInterface, public QObject
{
public:
    PaintLayer(const FriendMapSettings* settings, DataModel* datamodel);
    ~PaintLayer();
    // Implemented from LayerInterface
    virtual QStringList renderPosition() const;

    // Implemented from LayerInterface
    virtual bool render( GeoPainter *painter, ViewportParams *viewport,
	                     const QString& renderPos = "NONE", GeoSceneLayer * layer = 0 );
    void setSettings(const FriendMapSettings& settings){
        mSettings = &settings;
    }

public slots:
    void genPeerCache();
private:
    const FriendMapSettings* mSettings;
    DataModel* data_model;
    RsPeers* rsPeers;
    RsDisc* rsDisc;
};

#endif // PAINTLAYER_H

