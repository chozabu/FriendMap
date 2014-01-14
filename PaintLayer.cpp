#include "PaintLayer.h"
#include <QMessageBox>
#include <QFileInfo>
#include <marble/GeoDataLineString.h>

PaintLayer::PaintLayer(RsPeers *peers, const FriendMapSettings *settings)
{
    this->rsPeers = peers;
    const std::string& geoip_data_path = settings->getGeoIpDataPath();
    this->geoip = GeoIP_open(geoip_data_path.c_str(), GEOIP_STANDARD);
    if(geoip == NULL){
        std::cerr<<"Error: GeoLiteCity.dat not found!"<<std::endl;
        //QMessageBox::information(this, tr("FriendMap"), QString(tr("Error: GeoLiteCity.dat not found!")));
    }

}

PaintLayer::~PaintLayer()
{
    delete geoip;
}

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

bool PaintLayer::render( GeoPainter *painter, ViewportParams *viewport,
                         const QString& renderPos, GeoSceneLayer * layer )
{
    std::list<std::string> gpg_ids;
    rsPeers->getGPGAcceptedList(gpg_ids);
    foreach(const std::string& gpg_id, gpg_ids){
        RsPeerDetails peer_details;
        //rsPeers->getGPGDetails(gpg_id, gpg_detail);
        rsPeers->getPeerDetails(gpg_id, peer_details);

        std::list<std::string> ssl_ids;
        rsPeers->getAssociatedSSLIds(gpg_id, ssl_ids);

		srand(42);

        foreach(const std::string& ssl_id, ssl_ids){
            RsPeerDetails peer_ssl_details;
            rsPeers->getPeerDetails(ssl_id, peer_ssl_details);
            if(peer_ssl_details.extAddr.compare("0.0.0.0")){
                //std::cout<<peer_ssl_details.extAddr<<"\n";
                GeoIPRecord *r = GeoIP_record_by_name(geoip, peer_ssl_details.extAddr.c_str());
				if(r){
					float xr = ((double) rand() / (RAND_MAX))-0.5f;
					float yr = ((double) rand() / (RAND_MAX))-0.5f;
					GeoDataCoordinates coordFar(r->longitude, r->latitude, 0.0, GeoDataCoordinates::Degree);
					GeoDataCoordinates coord(r->longitude+xr, r->latitude+yr, 0.0, GeoDataCoordinates::Degree);

					GeoDataLineString al;
					al.append(coord);
					al.append(coordFar);
					delete r;
					if(rsPeers->isOnline(ssl_id))
						painter->setPen(Qt::green);
					else
						painter->setPen(Qt::red);
					float rr = ((double) rand() / (RAND_MAX));
					painter->drawEllipse(coordFar, 10*rr, 10*rr);
					painter->drawPolyline(al);
					painter->drawEllipse(coord, 10, 10);
					painter->setPen(Qt::black);
					painter->drawText(coord, QString::fromStdString(peer_ssl_details.name));
				}
            }

        }

    }

    return true;
}
