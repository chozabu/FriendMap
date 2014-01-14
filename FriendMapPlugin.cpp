#include "FriendMapPlugin.h"
#include <QMessageBox>
#include <QIcon>

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
uint32_t RETROSHARE_PLUGIN_revision = SVN_REVISION_NUMBER ;

// This symbol contains the svn revision number grabbed from the executable.
// It will be tested by RS to load the plugin automatically, since it is safe to load plugins
// with same revision numbers, assuming that the revision numbers are up-to-date.
//
uint32_t RETROSHARE_PLUGIN_api = RS_PLUGIN_API_VERSION ;
}

FriendMapPlugin::FriendMapPlugin()
{
    Q_INIT_RESOURCE(images);
    mIcon = new QIcon(":/images/icon.png");
    settings = new FriendMapSettings();
    main_page = NULL;
}

FriendMapPlugin::~FriendMapPlugin()
{
    delete main_page;
    delete mIcon;
    delete settings;
}

MainPage* FriendMapPlugin::qt_page() const{
    //if(!main_page && settings->validPaths())
    main_page = new FriendMapPage(peers);
    main_page->setConfig(settings);
    return main_page;
}

ConfigPage* FriendMapPlugin::qt_config_page() const{
    FriendMapConfigPage* config_page = new FriendMapConfigPage(settings);
    if(main_page)
        config_page->setMainPage(main_page);
    return config_page;
}

QDialog* FriendMapPlugin::qt_about_page() const
{
    static QMessageBox *about_dialog = NULL ;

    if(about_dialog == NULL)
    {
        about_dialog = new QMessageBox() ;

        QString text ;
        text += QObject::tr("<h3>RetroShare FriendMap plugin</h3><br/>* Developer: Nyfor<br/>This plugin is based on Marble (http://marble.kde.org)") ;
        text += QObject::tr("<br/><br/>This is an experimental feature. Use it on your own risk.") ;

        about_dialog->setText(text) ;
        about_dialog->setStandardButtons(QMessageBox::Ok) ;
    }

    return about_dialog ;
}

QIcon* FriendMapPlugin::qt_icon() const
{
    return mIcon;
}

std::string FriendMapPlugin::getShortPluginDescription() const{
    return "This plugin shows a map with your friends.";
}
std::string FriendMapPlugin::getPluginName() const {
    return "FriendMap";
}
void FriendMapPlugin::getPluginVersion(int& major,int& minor,int& svn_rev) const{
    major = 0;
    minor = 0;
    svn_rev = SVN_REVISION_NUMBER ;
}

//
//========================== Plugin Interface ================================//
//
// Use these methods to access main objects from RetroShare.
//
void FriendMapPlugin::setInterfaces(RsPlugInInterfaces& interfaces){
    peers = interfaces.mPeers;
}

void FriendMapPlugin::setPlugInHandler(RsPluginHandler* pgHandler){
    mPlugInHandler = pgHandler;
    settings->setStdPaths(pgHandler);
}
