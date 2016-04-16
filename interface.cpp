#include "interface.h"
interface* interface::instance;

const RsPlugInInterfaces& interface::get() {
    return (instance->interfaces);
}

GeoIP* interface::getGeoIP() {
    return (instance->geoip);
}

void interface::setSetting(FriendMapSettings& settings) {
    if (instance->geoip == nullptr) {
        const std::string& geoip_data_path = settings.getGeoIpDataPath();
        instance->geoip = GeoIP_open(geoip_data_path.c_str(), GEOIP_STANDARD);
    }
}

void interface::init(const RsPlugInInterfaces& interfaces) {
    instance = new interface(interfaces);
}

interface::interface(RsPlugInInterfaces interfaces) : interfaces(std::move(interfaces)) {
    geoip = nullptr;
}
