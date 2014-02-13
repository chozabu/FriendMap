#include "FriendMapDetached.h"
#include "ui_FriendMapDetached.h"

FriendMapDetached::FriendMapDetached(const FriendMapController *controller) :
    MainPage(NULL),
    ui(new Ui::FriendMapDetached)
{
    ui->setupUi(this);
    connect(this->ui->btn_ShowMap, SIGNAL(clicked()), controller, SLOT(openWindow()));
}

FriendMapDetached::~FriendMapDetached()
{
    delete ui;
}
