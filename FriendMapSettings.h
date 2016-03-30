/*!
 * @file FriendMapSettings.h
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

#ifndef FRIENDMAPSETTINGS_H
#define FRIENDMAPSETTINGS_H

#include <retroshare/rsplugin.h>
#include <QString>
#include <QDir>
#include <marble/MarbleWidget.h>
#include <marble/MarbleDirs.h>

class FriendMapSettings
{
    friend class FriendMapConfigPage;
public:
    FriendMapSettings();
    void setStdPaths(RsPluginHandler* pgHandler);
    const std::string& getGeoIpDataPath() const {return this->geoip_data_path;}
    bool getShowGrid() const {return show_grid;}
    bool getShowLinks() const {return show_links;}
    bool getShowBorders() const {return show_borders;}
    bool getShowCities() const {return show_cities;}
    bool getShowIceLayer() const {return show_ice_layer;}
    bool getShowClouds() const {return show_clouds;}
    bool getShowCityLights() const {return show_city_lights;}
    bool getShowSunShading() const {return show_sun_shading;}
    bool getShowAvatars() const {return show_avatars;}
    bool getDetached() const {return detached;}
    Marble::Projection getProjection() const {return projection;}
    const std::string& getMapThemeId() const {return map_theme_id;}
    bool setMarblePath(const QDir &marble_path);
    bool validPaths()const{return !(this->geoip_data_path.empty());}
    void processSettings(bool load);
private:
    std::string geoip_data_path;
    QString marble_path;
    bool show_grid;
    bool show_links;
    bool show_borders;
    bool show_cities;
    bool show_ice_layer;
    bool show_clouds;
    bool show_city_lights;
    bool show_sun_shading;
    bool show_avatars;
    bool detached;

    Marble::Projection projection;
    std::string map_theme_id;
};

#endif // FRIENDMAPSETTINGS_H

// eof   

