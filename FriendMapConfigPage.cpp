#include "FriendMapConfigPage.h"
#include "ui_FriendMapConfigPage.h"
#include <QCheckBox>

FriendMapConfigPage::FriendMapConfigPage(FriendMapSettings* settings) :
    ui(new Ui::FriendMapConfigPage)
{
    ui->setupUi(this);
    this->settings = settings;
    this->main_page = NULL;
    load();
}

FriendMapConfigPage::~FriendMapConfigPage()
{
    delete ui;
}

void FriendMapConfigPage::load(){
    ui->projection_box->setCurrentIndex(settings->getProjection());
	ui->show_grid->setChecked(settings->show_grid);
	ui->show_links->setChecked(settings->show_links);
	ui->show_borders->setChecked(settings->show_borders);
	ui->show_cities->setChecked(settings->show_cities);
	ui->show_ice_layer->setChecked(settings->show_ice_layer);
	ui->show_clouds->setChecked(settings->show_clouds);
	ui->show_city_lights->setChecked(settings->show_city_lights);
	ui->show_sun_shading->setChecked(settings->show_sun_shading);

    ui->geoip_path_line->setText(QString::fromStdString(settings->geoip_data_path));
    ui->marble_path_line->setText(settings->marble_path);
}

bool FriendMapConfigPage::save(QString &errmsg){
	settings->show_grid = ui->show_grid->isChecked();
	settings->show_links = ui->show_links->isChecked();
	settings->show_borders = ui->show_borders->isChecked();
	settings->show_cities = ui->show_cities->isChecked();
	settings->show_ice_layer = ui->show_ice_layer->isChecked();
	settings->show_clouds = ui->show_clouds->isChecked();
	settings->show_city_lights = ui->show_city_lights->isChecked();
	settings->show_sun_shading = ui->show_sun_shading->isChecked();

    settings->projection = (Marble::Projection)ui->projection_box->currentIndex();
    settings->geoip_data_path = ui->geoip_path_line->text().toStdString();
#ifdef WIN32
    if(!settings->setMarblePath(ui->marble_path_line->text())){
        errmsg = "invalid marble path";
        return false;
    }
#endif
    if(main_page)
        main_page->setConfig(settings);
	settings->processSettings(false);
    return true;
}
