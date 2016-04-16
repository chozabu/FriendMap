#ifndef INTERFACE_H
#define INTERFACE_H

#include <GeoIP.h>
#include <retroshare/rsplugin.h>

#include "FriendMapSettings.h"

class interface {
    friend class FriendMapPlugin;

   public:
    static const RsPlugInInterfaces& get();
    static GeoIP* getGeoIP();

    static void setSetting(FriendMapSettings& settings);

   private:
    static void init(const RsPlugInInterfaces& interfaces);
    explicit interface(RsPlugInInterfaces  interfaces);
    const RsPlugInInterfaces interfaces;
    GeoIP* geoip;
    static interface* instance;
};

#endif  // INTERFACE_H
