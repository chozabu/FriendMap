/*! 
 * @file FriendMapConfigPage.cpp
 *  @author RetroShare Team
 *  
 * Copyright (C) 2014 - RetroShare Team
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

#include "FriendMapConfigPage.h"
#include "ui_FriendMapConfigPage.h"
#include <QCheckBox>

//!
//! \brief FriendMapConfigPage::FriendMapConfigPage
//! \param settings
//!
FriendMapConfigPage::FriendMapConfigPage(FriendMapSettings* settings) :
    ui(new Ui::FriendMapConfigPage)
{
    ui->setupUi(this);
    this->settings = settings;
    load();
}

//!
//! \brief FriendMapConfigPage::~FriendMapConfigPage
//! Destructor - destroys the user interface
//
FriendMapConfigPage::~FriendMapConfigPage()
{
    delete ui;
}

//!
//! \brief FriendMapConfigPage::load
//!
void FriendMapConfigPage::load(){
	int themeindex = ui->theme_dgml->findText(QString::fromStdString(settings->map_theme_id));
	if (themeindex<0)themeindex=0;
	ui->theme_dgml->setCurrentIndex(themeindex);
	ui->projection_box->setCurrentIndex(settings->getProjection());
	ui->show_grid->setChecked(settings->show_grid);
	ui->show_links->setChecked(settings->show_links);
	ui->show_borders->setChecked(settings->show_borders);
	ui->show_cities->setChecked(settings->show_cities);
	ui->show_ice_layer->setChecked(settings->show_ice_layer);
	ui->show_clouds->setChecked(settings->show_clouds);
	ui->show_city_lights->setChecked(settings->show_city_lights);
	ui->show_sun_shading->setChecked(settings->show_sun_shading);
	ui->show_avatars->setChecked(settings->show_avatars);

    ui->geoip_path_line->setText(QString::fromStdString(settings->geoip_data_path));
    ui->marble_path_line->setText(settings->marble_path);
}

//!
//! \brief FriendMapConfigPage::save
//! \param errmsg
//! \return
//!
bool FriendMapConfigPage::save(QString &errmsg)
{
    settings->show_grid = ui->show_grid->isChecked();
    settings->show_links = ui->show_links->isChecked();
    settings->show_borders = ui->show_borders->isChecked();
    settings->show_cities = ui->show_cities->isChecked();
    settings->show_ice_layer = ui->show_ice_layer->isChecked();
    settings->show_clouds = ui->show_clouds->isChecked();
    settings->show_city_lights = ui->show_city_lights->isChecked();
    settings->show_sun_shading = ui->show_sun_shading->isChecked();
    settings->show_avatars = ui->show_avatars->isChecked();

    settings->projection = (Marble::Projection)ui->projection_box->currentIndex();
    settings->map_theme_id = ui->theme_dgml->currentText().toStdString();
    settings->geoip_data_path = ui->geoip_path_line->text().toStdString();
    
#ifdef WIN32
    // why is this just for windows? On Linux returns warning for unused variable
    QString dir = QDir::fromNativeSeparators(ui->marble_path_line->text());
    if(!settings->setMarblePath(QDir(dir))){
        errmsg = "invalid marble path";
        return false;
    }
#endif
    
    emit configChanged();
    settings->processSettings(false); 
    errmsg = "";     // set errmsg to a null string
    return true;
}

// eof  
