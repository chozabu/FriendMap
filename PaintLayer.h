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

#include <GeoIP.h>
#include <marble/GeoDataDocument.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/GeoDataTreeModel.h>
#include <marble/GeoPainter.h>
#include <marble/LayerInterface.h>

#include "DataModel.h"
#include "FriendMapSettings.h"
#include "interface.h"

using namespace Marble;

/**
 * @brief Define class PaintLayer
 */
class PaintLayer : public LayerInterface, public QObject {
   public:
    PaintLayer(const FriendMapSettings* settings, DataModel* datamodel);
    ~PaintLayer();
    // Implemented from LayerInterface
    virtual QStringList renderPosition() const override;

    // Implemented from LayerInterface
    virtual bool render(GeoPainter* painter, ViewportParams*, const QString& = "NONE", GeoSceneLayer* = 0) override;
    void setSettings(const FriendMapSettings& settings) {
        mSettings = &settings;
    }

   private:
    const FriendMapSettings* mSettings;
    DataModel* data_model;
    RsPeers* rsPeers;
};

#endif  // PAINTLAYER_H
