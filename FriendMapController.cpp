#include "FriendMapController.h"
#include "FriendMapDetached.h"

FriendMapController::FriendMapController(QObject* parent) : QObject(parent) {
    settings = new FriendMapSettings();
    this->detached = settings->getDetached();
    mainPage = nullptr;
}

FriendMapController::~FriendMapController() {
    delete settings;
    if (friendMapPage != nullptr) {
        delete friendMapPage;
    }
}

MainPage* FriendMapController::qt_page() const {
    if (mainPage == nullptr) {
        if (detached) {
            mainPage = new FriendMapDetached(this);
        } else {
            friendMapPage = new FriendMapPage();
            friendMapPage->setConfig(settings);
            mainPage = friendMapPage;
        }
    }
    return mainPage;
}

ConfigPage* FriendMapController::qt_config_page() const {
    auto configPage = new FriendMapConfigPage(settings);
    connect(configPage, SIGNAL(configChanged()), this, SLOT(configChanged()));
    return configPage;
}

FriendMapSettings* FriendMapController::getSettings() {
    return settings;
}

void FriendMapController::configChanged() {
    if (friendMapPage != nullptr) {
        friendMapPage->setConfig(settings);
    }
}

void FriendMapController::openWindow() {
    if (friendMapPage.isNull()) {
        friendMapPage = new FriendMapPage();
        friendMapPage->setAttribute(Qt::WA_DeleteOnClose, true);
        friendMapPage->show();
        friendMapPage->setConfig(settings);
    } else {
        friendMapPage->activateWindow();
    }
}
