#include "FriendMapConfigPage.h"
#include "ui_FriendMapConfigPage.h"

FriendMapConfigPage::FriendMapConfigPage(FriendMapSettings* settings) :
    ui(new Ui::FriendMapConfigPage)
{
    ui->setupUi(this);
    this->settings = settings;
    this->main_page = NULL;
    //load();
}

FriendMapConfigPage::~FriendMapConfigPage()
{
    delete ui;
}

void FriendMapConfigPage::load(){
    ui->projection_box->setCurrentIndex(settings->getProjection());
    //ui->show_grid->setChecked(settings->show_grid);
    ui->geoip_path_line->setText(QString::fromStdString(settings->geoip_data_path));
    ui->marble_path_line->setText(settings->marble_path);
}

bool FriendMapConfigPage::save(QString &errmsg){
    //settings->show_grid = ui->show_grid;
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
    return true;
}
