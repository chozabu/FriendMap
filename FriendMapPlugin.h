/*!
 * @file FriendMapPlugin.h
 * @author Nyfor, RetroShare Team
 * 
 * Copyright (C) 2014 - Nyfor, RetroShare Team
 * 
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

#ifndef EXPORTTOOLSPLUGIN_H
#define EXPORTTOOLSPLUGIN_H

#include <retroshare/rsplugin.h>
#include "FriendMapPage.h"
#include "FriendMapConfigPage.h"
#include "FriendMapController.h"

class FriendMapPlugin : public RsPlugin
{
public:
    FriendMapPlugin();
    ~FriendMapPlugin();

    MainPage* qt_page()const;
    ConfigPage* qt_config_page() const;
    QDialog* qt_about_page() const;
    QIcon* qt_icon() const;

    std::string getShortPluginDescription() const;
	std::string getPluginName() const;
	virtual void getPluginVersion(int &major, int &minor, int &build, int &svn_rev) const;

    //
    //========================== Plugin Interface ================================//
    //
    // Use these methods to access main objects from RetroShare.
    //
    void setInterfaces(RsPlugInInterfaces& interfaces);
    void setPlugInHandler(RsPluginHandler* pgHandler);

private:    
    RsPluginHandler* mPlugInHandler;
    QIcon* mIcon;
    FriendMapController* controller;
};

#endif // EXPORTTOOLSPLUGIN_H
