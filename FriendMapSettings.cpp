/*!
 * @file FriendMapSettings.cpp
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

#include "FriendMapSettings.h"
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QMessageBox>
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
    this->detached = true;

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
	show_avatars = Settings->value("show_avatars").toBool();
	projection = (Marble::Projection)Settings->value("projection_type").toInt();
	map_theme_id = Settings->value("map_theme_id").toString().toStdString();

        if (map_theme_id.length() < 2)map_theme_id = "earth/bluemarble/bluemarble.dgml";
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
	Settings->setValue("show_avatars", show_avatars);
	Settings->setValue("projection_type", projection);
	Settings->setValue("map_theme_id", QString::fromStdString(map_theme_id));
    }

    Settings->endGroup();
}

//!
//! \brief FriendMapSettings::setMarblePath
//! \param marble_path
//! \return
//!
bool FriendMapSettings::setMarblePath(const QDir &marble_path)
{
    this->marble_path = QDir::toNativeSeparators(marble_path.canonicalPath());

    QDir plugins = QDir(marble_path);
    QDir data = QDir(marble_path);

    bool valid = plugins.cd("plugins") && data.cd("data");
    if(valid){
        Marble::MarbleDirs::setMarblePluginPath(plugins.canonicalPath());
        Marble::MarbleDirs::setMarbleDataPath(data.canonicalPath());
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
    //Finding marble installation
    //Included with the plugin, RS_folder/marble
    QDir marblepathlocal = QDir(QCoreApplication::applicationDirPath());
    if(marblepathlocal.cd("marble") && setMarblePath(marblepathlocal)){
        //found in RS folder, nothing to do
    }else{
        //look for it in Program Files
        QByteArray pfdir = qgetenv("PROGRAMFILES(X86)");
        if(pfdir.isNull() || pfdir.isEmpty()){
            pfdir = qgetenv("PROGRAMFILES");
        }

        //check it again
        if(!pfdir.isNull() && !pfdir.isEmpty()){
            QString path = QString(pfdir);
            QDir marblepathprogramfiles = QDir(QDir::fromNativeSeparators(path));
            if(marblepathprogramfiles.cd("marble") && setMarblePath(marblepathprogramfiles)){
                //found in Program Files, nothing to do
                //TODO: check installed marble version, only if somebody reports problem about it
            }else{
                QString message = QString("Marble not found in the following places, please install Marble and/or set the path manually in the options<br>");
                message += QString(QCoreApplication::applicationDirPath() + "/marble<br>");
                message += QString(path + "/marble<br>");
                QMessageBox::warning(NULL, "Marble not found", message);
            }
        }else{
            //this shouldn't happen on Windows
            QMessageBox::warning(NULL, "Program Files directory not found", "Are your enviroment variables correct?");
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

// eof  

