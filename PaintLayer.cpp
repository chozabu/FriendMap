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

//!
//! \brief PaintLayer::PaintLayer
//  Obtains settings and the map data file.
//! \param peers
//! \param settings
//!
PaintLayer::PaintLayer(const FriendMapSettings *settings, DataModel* datamodel):data_model(datamodel)
{
    this->rsPeers = interface::get().mPeers;
    this->mSettings = settings;
}

//!
//! \brief PaintLayer::~PaintLayer
//!
PaintLayer::~PaintLayer()
{

}

//!
//! \brief PaintLayer::renderPosition
//! \return
//!
QStringList PaintLayer::renderPosition() const
{
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
    QStringList layers = QStringList() << "ALWAYS_ON_TOP"<<"SURFACE" << "HOVERS_ABOVE_SURFACE";
    layers << "ORBIT" << "USER_TOOLS" << "STARS";
    return QStringList()<<layers.at(0);
}

//!
//! \brief PaintLayer::render
//! \param painter
//! \param viewport
//! \param renderPos
//! \param layer
//! \return
//!
bool PaintLayer::render( GeoPainter *painter, ViewportParams *viewport,
                         const QString& renderPos, GeoSceneLayer * layer )
{
    const std::list<GeoPeer>& geoPeers = data_model->getPeers();
    for(auto it = geoPeers.begin(); it != geoPeers.end(); it++){
        const GeoPeer& geoPeer = *it;
        foreach(const GeoPeerLoc& geoPeerLoc, geoPeer.getLocations()){
            srand(42);
            float rr = ((double) rand() / (RAND_MAX));
            const GeoDataCoordinates& offCoord = data_model->getPosition(geoPeerLoc);
            const GeoDataCoordinates& coord = geoPeerLoc.getCoordinates();
            QSharedPointer<GeoDataStyle> style = data_model->getStyle(geoPeerLoc.getSslId());
            GeoDataIconStyle iconStyle;
            if(mSettings->getShowAvatars()){
                iconStyle.setIcon( geoPeer.getAvatar().toImage() );
                iconStyle.setScale(0.3);
                style->setIconStyle(iconStyle);
            } else {
                style->setIconStyle(iconStyle);
            }
            if(rsPeers->isOnline(geoPeerLoc.getSslId())){
                painter->setPen(Qt::green);
                GeoDataLabelStyle online;
                online.setColor(Qt::darkGreen);
                style->setLabelStyle(online);
            } else {
                painter->setPen(Qt::red);
                GeoDataLabelStyle offline;
                offline.setColor(Qt::darkRed);
                style->setLabelStyle(offline);
            }
            painter->drawEllipse(coord, 2.5f+5.f*rr, 2.5f+5.f*rr);
            painter->drawEllipse(offCoord, 15, 15);

            GeoDataLineString cLine;
            cLine.append(offCoord);
            cLine.append(coord);
            painter->drawPolyline(cLine);

            if(mSettings->getShowLinks()){
                painter->setPen(Qt::yellow);
                foreach(const RsPgpId& gpg_id, geoPeer.getConnectionsList()){
                    const GeoPeer* const other = data_model->getPeer(gpg_id);
                    if (other && other->getLocations().length()>0){
                        GeoPeerLoc oloc = other->getLocations().first();
                        GeoDataLineString conLine;
                        conLine.append(oloc.getCoordinates());
                        conLine.append(geoPeerLoc.getCoordinates());
                        painter->drawPolyline(conLine);
                    } else std::cerr << "error, missing all locations for a peer\n";
                }
            }
        }
    }

    return true;
}
