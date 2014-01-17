#ifndef FRIENDMAPSETTINGS_H
#define FRIENDMAPSETTINGS_H

#include <retroshare/rsplugin.h>
#include <QString>
#include <marble/MarbleWidget.h>

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
    Marble::Projection getProjection() const {return projection;}
    const std::string& getMapThemeId() const {return map_theme_id;}
    bool setMarblePath(const QString &marble_path);
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

    Marble::Projection projection;
    std::string map_theme_id;
};

#endif // FRIENDMAPSETTINGS_H
