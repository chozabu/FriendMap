#include "FriendMapPage.h"
#include "ui_FriendMapPage.h"
#include <QMessageBox>
#include "PaintLayer.h"

FriendMapPage::FriendMapPage(RsPeers* peers) :
    ui(new Ui::FriendMapPage)
{
    ui->setupUi(this);
    ui->MarbleWidget->setShowCompass(false);
    ui->MarbleWidget->setShowCrosshairs(false);
    this->peers = peers;

}

FriendMapPage::~FriendMapPage()
{
    delete ui;
}

void FriendMapPage::setConfig(const FriendMapSettings* settings){
    ui->MarbleWidget->setShowGrid(settings->getShowGrid());
    ui->MarbleWidget->setProjection(settings->getProjection());
    ui->MarbleWidget->setMapThemeId(settings->getMapThemeId().c_str());
    if(settings->validPaths()){
        PaintLayer* layer = new PaintLayer(peers, settings);
        ui->MarbleWidget->addLayer(layer);
    } else {
        QMessageBox::information(this,
                                 tr("FriendMap"),
                                 QString(tr("GeoIP Data not found!")));
    }
}
