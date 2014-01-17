#include "FriendMapPage.h"
#include "ui_FriendMapPage.h"
#include <QMessageBox>

//!
//! \brief FriendMapPage::FriendMapPage
//! \param peers
//!
FriendMapPage::FriendMapPage(RsPeers* peers) :
    ui(new Ui::FriendMapPage)
{
    ui->setupUi(this);
    ui->MarbleWidget->setShowCompass(false);
	ui->MarbleWidget->setShowCrosshairs(false);
    this->peers = peers;

}

//!
//! \brief FriendMapPage::~FriendMapPage
//!
FriendMapPage::~FriendMapPage()
{
    delete ui;
}

//!
//! \brief FriendMapPage::setConfig
//! \param settings
//!
void FriendMapPage::setConfig(const FriendMapSettings* settings){
    ui->MarbleWidget->setShowGrid(settings->getShowGrid());
    ui->MarbleWidget->setProjection(settings->getProjection());
    ui->MarbleWidget->setMapThemeId(settings->getMapThemeId().c_str());

	ui->MarbleWidget->setShowBorders(settings->getShowBorders());
	ui->MarbleWidget->setShowCities(settings->getShowCities());
	ui->MarbleWidget->setShowIceLayer(settings->getShowIceLayer());
	ui->MarbleWidget->setShowClouds(settings->getShowClouds());
	ui->MarbleWidget->setShowCityLights(settings->getShowCityLights());
	ui->MarbleWidget->setShowSunShading(settings->getShowSunShading());
    if(settings->validPaths()){
		if(layer)ui->MarbleWidget->removeLayer(layer);
		layer = new PaintLayer(peers, settings);
		//connect(ui->MarbleWidget, SIGNAL(mouseClickGeoPosition(qreal,qreal,GeoDataCoordinates::Unit)), layer, SLOT(genPeerCache());//enable to update cache on click
        ui->MarbleWidget->addLayer(layer);
    } else {
        QMessageBox::information(this,
                                 tr("FriendMap"),
                                 QString(tr("GeoIP Data not found!")));
    }
}
