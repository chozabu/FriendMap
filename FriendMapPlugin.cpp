/*!
 * @file FriendMapPlugin.cpp
 * @author Nyfor, RetroShare Team
 * 
 * Copyright (C) 2014 - RetroShare Team
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

#include "FriendMapPlugin.h"
#include "interface.h"
//!
//!
//!
extern "C" {
void *RETROSHARE_PLUGIN_provide()
{
    static FriendMapPlugin* p = new FriendMapPlugin() ;
    return (void*)p ;
}
// This symbol contains the svn revision number grabbed from the executable.
// It will be tested by RS to load the plugin automatically, since it is safe to load plugins
// with same revision numbers, assuming that the revision numbers are up-to-date.
//
uint32_t RETROSHARE_PLUGIN_revision = RS_REVISION_NUMBER ;

// This symbol contains the svn revision number grabbed from the executable.
// It will be tested by RS to load the plugin automatically, since it is safe to load plugins
// with same revision numbers, assuming that the revision numbers are up-to-date.
//
uint32_t RETROSHARE_PLUGIN_api = RS_PLUGIN_API_VERSION ;
}

//!
//! \brief FriendMapPlugin::FriendMapPlugin
//!
FriendMapPlugin::FriendMapPlugin()
{
    Q_INIT_RESOURCE(images);
    mIcon = new QIcon(":/images/globeicon.png");
    controller = new FriendMapController();
}

//!
//! \brief FriendMapPlugin::~FriendMapPlugin
//!
FriendMapPlugin::~FriendMapPlugin()
{
    delete mIcon;
    delete controller;
}

//!
//! \brief FriendMapPlugin::qt_page
//! \return
//!
MainPage* FriendMapPlugin::qt_page() const
{
    return controller->qt_page();
}

//!
//! \brief FriendMapPlugin::qt_config_page
//! \return
//!
ConfigPage* FriendMapPlugin::qt_config_page() const
{
    return controller->qt_config_page();
}

//!
//! \brief FriendMapPlugin::qt_about_page
//! \return
//!
QDialog* FriendMapPlugin::qt_about_page() const
{
    static QMessageBox *about_dialog = NULL ;

    if(about_dialog == NULL)
    {
        about_dialog = new QMessageBox() ;

        QString text ;
        text += QObject::tr("<h3>RetroShare FriendMap plugin</h3><br/>* Developer: Nyfor<br/>This plugin is based on Marble (http://marble.kde.org)") ;
        text += QObject::tr("<br/><br/>FriendMap shows selected map with your friends location.");
        text += QObject::tr("<br/><br/>This is an experimental feature. Use it on your own risk.") ;

        about_dialog->setText(text) ;
        about_dialog->setStandardButtons(QMessageBox::Ok) ;
    }

    return about_dialog ;
}

//!
//! \brief FriendMapPlugin::qt_icon
//! \return
//!
QIcon* FriendMapPlugin::qt_icon() const
{
    return mIcon;
}

//!
//! \brief FriendMapPlugin::getShortPluginDescription
//! \return
//!
std::string FriendMapPlugin::getShortPluginDescription() const
{
    return "This plugin shows a map with your friends.";
}

//!
//! \brief FriendMapPlugin::getPluginName
//! \return
//!
std::string FriendMapPlugin::getPluginName() const 
{
    return "FriendMap";
}

//!
//! \brief FriendMapPlugin::getPluginVersion
//! \param major
//! \param minor
//! \param svn_rev
//!
void FriendMapPlugin::getPluginVersion(int& major, int& minor, int &build, int& svn_rev) const
{
	major = RS_MAJOR_VERSION;
	minor = RS_MINOR_VERSION;
	build = RS_BUILD_NUMBER;
	svn_rev = RS_REVISION_NUMBER;
}


//
//========================== Plugin Interface ================================//
//
// Use these methods to access main objects from RetroShare.
//
//!
//! \brief FriendMapPlugin::setInterfaces
//! \param interfaces
//!
void FriendMapPlugin::setInterfaces(RsPlugInInterfaces& interfaces)
{
    interface::init(interfaces);
}

//!
//! \brief FriendMapPlugin::setPlugInHandler
//! \param pgHandler
//!
void FriendMapPlugin::setPlugInHandler(RsPluginHandler* pgHandler)
{
    mPlugInHandler = pgHandler;
    controller->getSettings()->setStdPaths(pgHandler);
}

// eof   

