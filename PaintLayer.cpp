#include "PaintLayer.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QMap>
#include <QFont>
#include <math.h>
#include <retroshare/rsdisc.h>
#include <marble/GeoDataLineString.h>
#include "gui/common/AvatarDefs.h"

#define PI 3.14159265

//!
//! \brief PaintLayer::PaintLayer
//! \param peers
//! \param settings
//!
PaintLayer::PaintLayer(RsPeers *peers, const FriendMapSettings *settings)
{
    this->rsPeers = peers;
	this->mSettings = settings;
    const std::string& geoip_data_path = settings->getGeoIpDataPath();
	showingLinks = settings->getShowLinks();
    this->geoip = GeoIP_open(geoip_data_path.c_str(), GEOIP_STANDARD);
    if(geoip == NULL){
        std::cerr<<"Error: GeoLiteCity.dat not found!"<<std::endl;
        //QMessageBox::information(this, tr("FriendMap"), QString(tr("Error: GeoLiteCity.dat not found!")));
    }
	genPeerCache();

}

//!
//! \brief PaintLayer::~PaintLayer
//!
PaintLayer::~PaintLayer()
{
    delete geoip;
}

//!
//! \brief PaintLayer::renderPosition
//! \return
//!
QStringList PaintLayer::renderPosition() const
{
    // We will paint in exactly one of the following layers.
    // The current one can be changed by pressing the '+' key
    /*
     * "NONE"
     * "STARS"
     * "BEHIND_TARGET"
     * "SURFACE"
     * "HOVERS_ABOVE_SURFACE"
     * "ATMOSPHERE"
     * "ORBIT"
     * "ALWAYS_ON_TOP"
     * "FLOAT_ITEM"
     * "USER_TOOLS"
     */
    QStringList layers = QStringList() << "ALWAYS_ON_TOP"<<"SURFACE" << "HOVERS_ABOVE_SURFACE";
    layers << "ORBIT" << "USER_TOOLS" << "STARS";
    return QStringList()<<layers.at(0);
}

//!
//! \brief The GeoPeerLoc class
//!
class GeoPeerLoc{
public:
	QString gpg_id;
	QString ssl_id;
	QString name;
	GeoDataCoordinates coord;
	GeoDataCoordinates coordOff;

};

//!
//! \brief The GeoPeer class
//!
class GeoPeer{
public:
	QString gpg_id;
	QList<GeoPeerLoc> locations;
	//QMap<QString, GeoPeer> connections;//could use this
	QList<std::string> connectionsList;
	QPixmap avatar;
};

//!
//!//! \brief geoPeers
//!

QList<GeoPeer> geoPeers;
QMap<std::string, GeoPeer> peerTable;
void PaintLayer::genPeerCache(){

	srand(42);

	std::list<std::string> gpg_ids;
    rsPeers->getGPGAcceptedList(gpg_ids);
	gpg_ids.push_back(rsPeers->getGPGId(rsPeers->getOwnId()));

	//QList<GeoPeer> geoPeers;
	//QMap<QString, GeoPeer> peerTable;
	geoPeers.clear();
	peerTable.clear();
	//LIST GPG
	foreach(const std::string& gpg_id, gpg_ids){
		GeoPeer gFriend;
		gFriend.locations.clear();
        RsPeerDetails peer_details;
        //rsPeers->getGPGDetails(gpg_id, gpg_detail);
        rsPeers->getPeerDetails(gpg_id, peer_details);

        std::list<std::string> ssl_ids;
        rsPeers->getAssociatedSSLIds(gpg_id, ssl_ids);

		//LIST SSL
        foreach(const std::string& ssl_id, ssl_ids){
            RsPeerDetails peer_ssl_details;
            rsPeers->getPeerDetails(ssl_id, peer_ssl_details);
            if(peer_ssl_details.extAddr.compare("0.0.0.0")){
                //std::cout<<peer_ssl_details.extAddr<<"\n";
                GeoIPRecord *r = GeoIP_record_by_name(geoip, peer_ssl_details.extAddr.c_str());
				if(r){
					GeoPeerLoc sLocation;
					sLocation.coord = GeoDataCoordinates(r->longitude, r->latitude, 0.0, GeoDataCoordinates::Degree);

					float rr = ((double) rand() / (RAND_MAX))*PI*2.0f;
					sLocation.coordOff = GeoDataCoordinates(r->longitude+cos(rr)*0.3f, r->latitude+sin(rr)*0.3f, 0.0, GeoDataCoordinates::Degree);
					sLocation.ssl_id = QString::fromStdString(ssl_id);
					sLocation.name = QString::fromUtf8(peer_ssl_details.name.c_str());
					gFriend.locations.push_back(sLocation);
				}

            }

        }
		if(gFriend.locations.length()>0){
			gFriend.gpg_id = QString::fromStdString(gpg_id);

			if(mSettings->getShowAvatars()){
				AvatarDefs::getAvatarFromGpgId(gpg_id, gFriend.avatar);
				gFriend.avatar = gFriend.avatar.scaledToWidth(22);
			}
			geoPeers.push_back(gFriend);
			peerTable.insert(gpg_id,gFriend);
		}

    }

	//Cache connections
	QList<GeoPeer>::iterator geoPeer;
	for (geoPeer = geoPeers.begin(); geoPeer != geoPeers.end(); ++geoPeer){
	//foreach(GeoPeer geoPeer, geoPeers){
		std::list<std::string> friendList;
		rsDisc->getDiscGPGFriends(geoPeer->gpg_id.toStdString(), friendList);
		//geoPeer->connections.clear();
		geoPeer->connectionsList.clear();
		foreach(const std::string& gpg_id, friendList){
			if (peerTable.contains(gpg_id)){
			//QString q_id = QString::fromStdString(gpg_id);
			//GeoPeer gp = peerTable[q_id];
			//geoPeer->connections.insert(q_id,gp);
			geoPeer->connectionsList.push_back(gpg_id);
			}
		}

    }

}

//!
//! \brief PaintLayer::render
//! \param painter
//! \param viewport
//! \param renderPos
//! \param layer
//! \return
//!
bool PaintLayer::render( GeoPainter *painter, ViewportParams *viewport,
                         const QString& renderPos, GeoSceneLayer * layer )
{

	srand(42);

	foreach(const GeoPeer& geoPeerc, geoPeers){
		GeoPeer geoPeer = geoPeerc;

		foreach(const GeoPeerLoc& geoPeerLoc, geoPeer.locations){

			float rr = ((double) rand() / (RAND_MAX));
			//GeoDataCoordinates coord = geoPeerLoc.coord;
			GeoDataCoordinates coord = geoPeerLoc.coordOff;
			//std::cerr << "FRIENDMAP: show avatars: " << mSettings->getShowAvatars() << "\n";
			if(mSettings->getShowAvatars())
				painter->drawPixmap(coord, geoPeer.avatar);

			if(rsPeers->isOnline(geoPeerLoc.ssl_id.toStdString()))
				painter->setPen(Qt::green);
			else
				painter->setPen(Qt::red);
			painter->drawEllipse(geoPeerLoc.coord, 2.5f+5.f*rr, 2.5f+5.f*rr);
			painter->drawEllipse(coord, 10, 10);

			GeoDataLineString cLine;
			cLine.append(coord);
			cLine.append(geoPeerLoc.coord);
			painter->drawPolyline(cLine);

			painter->setPen(Qt::white);
			QFont fonz;
			fonz.setBold(true);
			fonz.setStyleStrategy(QFont::ForceOutline);
			painter->setFont(fonz);
			painter->drawText(coord, geoPeerLoc.name);


			if(showingLinks){
				painter->setPen(Qt::yellow);
				foreach(const std::string& gpg_id, geoPeer.connectionsList){
					GeoPeer other = peerTable[gpg_id];
					if (other.locations.length()>0){
						GeoPeerLoc oloc = other.locations.first();
						GeoDataLineString conLine;
						conLine.append(oloc.coord);
						conLine.append(geoPeerLoc.coord);
						painter->drawPolyline(conLine);
					} else std::cerr << "error, missing all locations for a peer\n";
				}
			}
		}
	}

    return true;
}
