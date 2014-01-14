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
    Marble::Projection getProjection() const {return projection;}
    const std::string& getMapThemeId() const {return map_theme_id;}
    bool setMarblePath(const QString &marble_path);
    bool validPaths()const{return !(this->geoip_data_path.empty());}
private:
    std::string geoip_data_path;
    QString marble_path;
    bool show_grid;
    Marble::Projection projection;
    std::string map_theme_id;
};

#endif // FRIENDMAPSETTINGS_H
