/*!
 * @file PaintLayer.cpp
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

#include "PaintLayer.h"
#include "GeoLink.h"
#include "GeoTunnel.h"

//!
//! \brief PaintLayer::PaintLayer
//  Obtains settings and the map data file.
//! \param peers
//! \param settings
//!
PaintLayer::PaintLayer(const FriendMapSettings* settings, DataModel* datamodel) : data_model(datamodel) {
    this->rsPeers = interface::get().mPeers;
    this->mSettings = settings;
}

//!
//! \brief PaintLayer::~PaintLayer
//!
PaintLayer::~PaintLayer() = default;

//!
//! \brief PaintLayer::renderPosition
//! \return
//!
QStringList PaintLayer::renderPosition() const {
    // We will paint in exactly one of the following layers.
    // The current one can be changed by pressing the '+' key
    /*
     * "NONE"
     * "STARS"
     * "BEHIND_TARGET"
     * "SURFACE"
     * "HOVERS_ABOVE_SURFACE"
     * "ATMOSPHERE"
     * "ORBIT"
     * "ALWAYS_ON_TOP"
     * "FLOAT_ITEM"
     * "USER_TOOLS"
     */
    QStringList layers = QStringList() << "ALWAYS_ON_TOP"
                                       << "SURFACE"
                                       << "HOVERS_ABOVE_SURFACE";
    layers << "ORBIT"
           << "USER_TOOLS"
           << "STARS";
    return QStringList() << layers.at(0);
}

//!
//! \brief PaintLayer::render
//! \param painter
//! \param viewport
//! \param renderPos
//! \param layer
//! \return
//!
bool PaintLayer::render(GeoPainter* painter, ViewportParams* /*viewport*/, const QString& /*renderPos*/, GeoSceneLayer* /*layer*/) {
    {
        std::vector<std::vector<std::string> > hashes_info;
        std::vector<std::vector<std::string> > tunnels_info;
        std::vector<TurtleRequestDisplayInfo> search_reqs_info;
        std::vector<TurtleRequestDisplayInfo> tunnel_reqs_info;
        interface::get().mTurtle->getInfo(hashes_info, tunnels_info, search_reqs_info, tunnel_reqs_info);

        foreach (const std::vector<std::string>& tunnel_str, tunnels_info) {
            TurtleTunnelInfo tunnel(tunnel_str, *data_model);
            GeoTunnel geotunnel(tunnel);
            geotunnel.paint(painter);
        }
    }
    if (mSettings->getShowLinks()) {
        auto geoPeers = data_model->getPeers();
        for (auto geoPeer : geoPeers) {
            GeoLink peer_links(*geoPeer, data_model);
            peer_links.paint(painter);
        }
    }

    return true;
}
