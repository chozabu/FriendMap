#ifndef FRIENDMAPMANAGER_H
#define FRIENDMAPMANAGER_H

#include <retroshare-gui/mainpage.h>
#include <retroshare/rsplugin.h>
#include <QObject>
#include <QPointer>
#include "FriendMapConfigPage.h"
#include "FriendMapPage.h"
#include "FriendMapSettings.h"

class FriendMapController : public QObject {
    Q_OBJECT
   public:
    explicit FriendMapController(QObject* parent = 0);
    ~FriendMapController();
    MainPage* qt_page() const;
    ConfigPage* qt_config_page() const;
    FriendMapSettings* getSettings();

   private:
    bool detached;  //cache settings value to do not allow to change it at runtime
    FriendMapSettings* settings;
    mutable MainPage* mainPage;
    mutable QPointer<FriendMapPage> friendMapPage;

   signals:

   public slots:
    void configChanged();
    void openWindow();
};

#endif  // FRIENDMAPMANAGER_H
