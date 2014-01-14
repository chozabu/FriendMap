#ifndef FRIENDMAPPAGE_H
#define FRIENDMAPPAGE_H

#include <QWidget>
#include <retroshare-gui/mainpage.h>
#include <retroshare/rsplugin.h>
#include "FriendMapSettings.h"

namespace Ui {
class FriendMapPage;
}

class FriendMapPage : public MainPage
{
    Q_OBJECT
    
public:
    explicit FriendMapPage(RsPeers*);
    void setConfig(const FriendMapSettings* settings);
    ~FriendMapPage();
    
private:
    Ui::FriendMapPage *ui;
    RsPeers* peers;
};

#endif // FRIENDMAPPAGE_H
