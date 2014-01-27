/*!
 * @file FriendMapConfigPage.h
 * @author Nyfor, RetroShare Team
 * 
 * Copyright (C) 2014 - Nyfor
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

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
    virtual QPixmap iconPixmap() const { return QPixmap(":/images/globeicon.png"); }

    // Name of the page, to put in the leftside list
    //
    virtual QString pageName() const {return "FriendMap";}


	virtual QString helpText() const {return "No Help. Sorry.";}

    void setMainPage(FriendMapPage *main_page){this->main_page = main_page;}
    
private:
    Ui::FriendMapConfigPage *ui;
    FriendMapSettings* settings;
    FriendMapPage *main_page;
};

#endif // FRIENDMAPCONFIGPAGE_H
