#include "FriendMapController.h"

FriendMapController::FriendMapController(QObject *parent) :
    QObject(parent)
{
    settings = new FriendMapSettings();
}

FriendMapController::~FriendMapController()
{
    delete settings;
    delete mainPage;
    if(friendMapPage)
        delete friendMapPage;
}

MainPage *FriendMapController::qt_page() const
{
    friendMapPage = new FriendMapPage(peers, mDisc);
    mainPage = friendMapPage;
    friendMapPage->setConfig(settings);
    return mainPage;
}

ConfigPage *FriendMapController::qt_config_page() const
{
    FriendMapConfigPage* configPage = new FriendMapConfigPage(settings);
    connect(configPage, SIGNAL(configChanged()), this, SLOT(configChanged()));
    return configPage;
}

FriendMapSettings *FriendMapController::getSettings()
{
    return settings;
}

void FriendMapController::configChanged()
{
    if(friendMapPage)
        friendMapPage->setConfig(settings);
}
