#ifndef TURTLETUNNELINFO_H
#define TURTLETUNNELINFO_H

#include <QtGlobal>
#include "DataModel.h"
#include "turtle/p3turtle.h"
#include "turtle/turtletypes.h"

enum TunnelType {
    Download,
    Upload,
    Mediator
};

class TurtleTunnelInfo {
   public:
    TurtleTunnelInfo(const std::vector<std::string>& tunnels_info_str, const DataModel& dm);

    const TurtleTunnelId& getId() const;

    const TurtlePeerId& getSourceID() const;

    const TurtlePeerId& getDestinationID() const;

    double getSpeedBps() const;

    const std::string& getIdString() const;
    std::string toString() const;

    const std::string& getHash() const {
        return hash;
    }

    TunnelType getType() const;

   private:
    TurtleTunnelId id;
    std::string id_str;
    TurtlePeerId source_id;
    TurtlePeerId destination_id;
    std::string hash;
    std::string secs_ago;
    double speed_Bps;
    std::string speed_Bps_str;
};

#endif
