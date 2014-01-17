#ifndef FRIENDMAPPAGE_H
#define FRIENDMAPPAGE_H

#include <QWidget>
#include <QTimer>
#include <retroshare-gui/mainpage.h>
#include <retroshare/rsplugin.h>
#include "FriendMapSettings.h"
#include "PaintLayer.h"

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
	QTimer mTimer;
    Ui::FriendMapPage *ui;
    RsPeers* peers;
	PaintLayer* layer;
};

#endif // FRIENDMAPPAGE_H
