#ifndef FRIENDMAPMANAGER_H
#define FRIENDMAPMANAGER_H

#include <QObject>
#include <QPointer>
#include <retroshare/rsplugin.h>
#include "FriendMapSettings.h"
#include "FriendMapPage.h"
#include "FriendMapConfigPage.h"
#include <retroshare-gui/mainpage.h>

class FriendMapController : public QObject
{
    Q_OBJECT
public:
    RsPeers* peers;
    RsDisc*  mDisc;
    explicit FriendMapController(QObject *parent = 0);
    ~FriendMapController();
    MainPage* qt_page()const;
    ConfigPage* qt_config_page() const;
    FriendMapSettings* getSettings();

private:
    FriendMapSettings* settings;
    mutable MainPage* mainPage;
    mutable QPointer<FriendMapPage> friendMapPage;

signals:

public slots:
    void configChanged();
};

#endif // FRIENDMAPMANAGER_H
