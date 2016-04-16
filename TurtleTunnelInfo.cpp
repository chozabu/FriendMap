#include "TurtleTunnelInfo.h"

TurtleTunnelInfo::TurtleTunnelInfo(const std::vector<std::string>& tunnels_info_str, const DataModel& dm) {
    auto it = tunnels_info_str.begin();
    id_str = *it;
    id = (std::stol(*it, nullptr, 16));
    it++;
    source_id = TurtlePeerId(*it);
    if (source_id.isNull()) {
        source_id = dm.getLocationByName(*it);
    }
    it++;
    destination_id = TurtlePeerId(*it);
    if (destination_id.isNull()) {
        destination_id = dm.getLocationByName(*it);
    }
    it++;
    hash = *it;
    it++;
    secs_ago = *it;
    it++;
    speed_Bps_str = (*it);
    const std::string& s = speed_Bps_str;
    speed_Bps = std::stod(s.substr(0, s.find(" ")));
    const std::string unit = s.substr(s.find(" "));
    if (unit.find('K') != std::string::npos) {
        speed_Bps *= 1024;
    } else if (unit.find('M') != std::string::npos) {
        speed_Bps *= 1024 * 1024;
    } else if (unit.find('G') != std::string::npos) {
        speed_Bps *= 1024 * 1024 * 1024;
    }
}

const TurtleTunnelId& TurtleTunnelInfo::getId() const {
    return id;
}

const TurtlePeerId& TurtleTunnelInfo::getSourceID() const {
    return source_id;
}

const TurtlePeerId& TurtleTunnelInfo::getDestinationID() const {
    return destination_id;
}

double TurtleTunnelInfo::getSpeedBps() const {
    return speed_Bps;
}

const std::string& TurtleTunnelInfo::getIdString() const {
    return id_str;
}

std::string TurtleTunnelInfo::toString() const {
    return id_str + "\n" + speed_Bps_str + "\n" + std::to_string(speed_Bps) + "\n" + hash;
}

TunnelType TurtleTunnelInfo::getType() const {
    const RsPeerId& own = interface::get().mPeers->getOwnId();
    TunnelType type = TunnelType::Mediator;
    if (source_id == own) {
        type = TunnelType::Download;
    } else if (destination_id == own) {
        type = TunnelType::Upload;
    }
    return type;
}
