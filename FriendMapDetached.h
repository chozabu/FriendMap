#ifndef FRIENDMAPDETACHED_H
#define FRIENDMAPDETACHED_H

#include <retroshare-gui/mainpage.h>
#include <QWidget>
#include "FriendMapController.h"

namespace Ui {
class FriendMapDetached;
}

class FriendMapDetached : public MainPage {
    Q_OBJECT

   public:
    explicit FriendMapDetached(const FriendMapController* controller = 0);
    ~FriendMapDetached();

   private:
    Ui::FriendMapDetached* ui;
};

#endif  // FRIENDMAPDETACHED_H
