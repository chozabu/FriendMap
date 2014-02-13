#include "FriendMapDetached.h"
#include "ui_FriendMapDetached.h"

FriendMapDetached::FriendMapDetached(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendMapDetached)
{
    ui->setupUi(this);
}

FriendMapDetached::~FriendMapDetached()
{
    delete ui;
}
