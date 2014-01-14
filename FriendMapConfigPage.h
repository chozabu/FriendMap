#ifndef FRIENDMAPCONFIGPAGE_H
#define FRIENDMAPCONFIGPAGE_H

#include <retroshare/rsplugin.h>
#include "retroshare-gui/configpage.h"
#include "FriendMapSettings.h"
#include "FriendMapPage.h"
#include <QPixmap>

namespace Ui {
class FriendMapConfigPage;
}

class FriendMapConfigPage : public ConfigPage
{
    Q_OBJECT
    
public:
    explicit FriendMapConfigPage(FriendMapSettings *settings);
    ~FriendMapConfigPage();

    virtual void load();

    /** Pages save their config settings here
     * and return true if everything was saved successfully. */
    virtual bool save(QString &errmsg);

    // Icon to be used to display the config page.
    //
    virtual QPixmap iconPixmap() const { return QPixmap(":/images/icon.png"); }

    // Name of the page, to put in the leftside list
    //
    virtual QString pageName() const {return "FriendMap";}

    void setMainPage(FriendMapPage *main_page){this->main_page = main_page;}
    
private:
    Ui::FriendMapConfigPage *ui;
    FriendMapSettings* settings;
    FriendMapPage *main_page;
};

#endif // FRIENDMAPCONFIGPAGE_H
