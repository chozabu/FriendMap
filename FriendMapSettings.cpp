#include "FriendMapSettings.h"
#include <QFile>
#include <marble/MarbleDirs.h>
#include "gui/settings/rsharesettings.h"

//!
//! \brief FriendMapSettings::FriendMapSettings
//!
FriendMapSettings::FriendMapSettings()
{
	this->show_grid = false;
	this->show_links = true;
    this->projection = Marble::Spherical;
    this->geoip_data_path = "";

    //earth/openstreetmap/openstreetmap.dgml
    //earth/plain/plain.dgml
    //earth/schagen1689/schagen1689.dgml
    //"earth/citylights/citylights.dgml"
	//this->map_theme_id = "earth/openstreetmap/openstreetmap.dgml";
	this->map_theme_id = "earth/bluemarble/bluemarble.dgml";
	processSettings(true);
}

//!
//! \brief FriendMapSettings::processSettings
//! \param load
//!
void FriendMapSettings::processSettings(bool load)
{
	Settings->beginGroup(QString("FriendMapSettings"));

	if (load) {
		// load settings

		show_grid = Settings->value("show_grid").toBool();
		show_links = Settings->value("show_links").toBool();
		show_borders = Settings->value("show_borders").toBool();
		show_cities = Settings->value("show_cities").toBool();
		show_ice_layer = Settings->value("show_ice_layer").toBool();
		show_clouds = Settings->value("show_clouds").toBool();
		show_city_lights = Settings->value("show_city_lights").toBool();
		show_sun_shading = Settings->value("show_sun_shading").toBool();
	} else {
		// save settings
		Settings->setValue("show_grid", show_grid);
		Settings->setValue("show_links", show_links);
		Settings->setValue("show_borders", show_borders);
		Settings->setValue("show_cities", show_cities);
		Settings->setValue("show_ice_layer", show_ice_layer);
		Settings->setValue("show_clouds", show_clouds);
		Settings->setValue("show_city_lights", show_city_lights);
		Settings->setValue("show_sun_shading", show_sun_shading);
	}

	Settings->endGroup();
}

//!
//! \brief FriendMapSettings::setMarblePath
//! \param marble_path
//! \return
//!
bool FriendMapSettings::setMarblePath(const QString& marble_path){
    this->marble_path = marble_path;
    if(!(marble_path.endsWith('\\') || marble_path.endsWith('/'))){
        this->marble_path += '/';
    }
    this->marble_path = QDir::toNativeSeparators(this->marble_path);
    QString marble_plugin_path = marble_path+"plugins";
    QString marble_data_path = marble_path+"data";

    QFileInfo fipp(marble_plugin_path);
    QFileInfo fidp(marble_data_path);
    bool valid = fipp.exists() & fidp.exists();
    if(valid){
        Marble::MarbleDirs::setMarblePluginPath(marble_plugin_path);
        Marble::MarbleDirs::setMarbleDataPath(marble_data_path);
    }
    return valid;
}

//!
//! \brief FriendMapSettings::setStdPaths
//! \param pgHandler
//!
void FriendMapSettings::setStdPaths(RsPluginHandler *pgHandler)
{
#ifdef WIN32
    QString marble_search_path = ":\\Program Files (x86)\\Marble";
    for(char drive_letter='C'; drive_letter<'C'+23; drive_letter++){
        QFileInfo finfo(drive_letter+marble_search_path);
        if(finfo.exists()){
            marble_path = finfo.canonicalFilePath();
            this->setMarblePath(marble_path);
            break;
        }
    }
#endif

    const std::vector<std::string>& plugin_directories = pgHandler->getPluginDirectories();
    foreach(const std::string& dir, plugin_directories){
        QFileInfo finfo(QString::fromStdString(dir+"GeoLiteCity.dat"));
        std::cout<<QString::fromStdString(dir+"GeoLiteCity.dat").toStdString();
        if(finfo.exists()){
            geoip_data_path = QDir::toNativeSeparators(finfo.canonicalFilePath()).toStdString();
            break;
        }
    }
}
