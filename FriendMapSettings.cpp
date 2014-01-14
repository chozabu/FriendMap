#include "FriendMapSettings.h"
#include <QFile>
#include <marble/MarbleDirs.h>


FriendMapSettings::FriendMapSettings()
{
    this->show_grid = false;
    this->projection = Marble::Spherical;
    this->geoip_data_path = "";

    //earth/openstreetmap/openstreetmap.dgml
    //earth/plain/plain.dgml
    //earth/schagen1689/schagen1689.dgml
    //"earth/citylights/citylights.dgml"
    this->map_theme_id = "earth/openstreetmap/openstreetmap.dgml";
}

bool FriendMapSettings::setMarblePath(const QString& marble_path){
    this->marble_path = marble_path;
    if(!(marble_path.endsWith('\\') || marble_path.endsWith('/'))){
        this->marble_path += '/';
    }
    this->marble_path = QDir::toNativeSeparators(this->marble_path);
    QString marble_plugin_path = marble_path+"plugins";
    QString marble_data_path = marble_path+"data";

    QFileInfo fipp(marble_plugin_path);
    QFileInfo fidp(marble_data_path);
    bool valid = fipp.exists() & fidp.exists();
    if(valid){
        Marble::MarbleDirs::setMarblePluginPath(marble_plugin_path);
        Marble::MarbleDirs::setMarbleDataPath(marble_data_path);
    }
    return valid;
}

void FriendMapSettings::setStdPaths(RsPluginHandler *pgHandler)
{
#ifdef WIN32
    QString marble_search_path = ":\\Program Files (x86)\\Marble";
    for(char drive_letter='C'; drive_letter<'C'+23; drive_letter++){
        QFileInfo finfo(drive_letter+marble_search_path);
        if(finfo.exists()){
            marble_path = finfo.canonicalFilePath();
            this->setMarblePath(marble_path);
            break;
        }
    }
#endif

    const std::vector<std::string>& plugin_directories = pgHandler->getPluginDirectories();
    foreach(const std::string& dir, plugin_directories){
        QFileInfo finfo(QString::fromStdString(dir+"GeoLiteCity.dat"));
        std::cout<<QString::fromStdString(dir+"GeoLiteCity.dat").toStdString();
        if(finfo.exists()){
            geoip_data_path = QDir::toNativeSeparators(finfo.canonicalFilePath()).toStdString();
            break;
        }
    }
}
