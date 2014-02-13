#ifndef FRIENDMAPDETACHED_H
#define FRIENDMAPDETACHED_H

#include <QWidget>
#include <retroshare-gui/mainpage.h>

namespace Ui {
class FriendMapDetached;
}

class FriendMapDetached : public MainPage
{
    Q_OBJECT

public:
    explicit FriendMapDetached(QWidget *parent = 0);
    ~FriendMapDetached();

private:
    Ui::FriendMapDetached *ui;
};

#endif // FRIENDMAPDETACHED_H
