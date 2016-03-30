#ifndef INTERFACE_H
#define INTERFACE_H

#include <retroshare/rsplugin.h>
#include <GeoIP.h>

#include "FriendMapSettings.h"

class interface
{
    friend class FriendMapPlugin;
public:
    static const RsPlugInInterfaces& get();
    static GeoIP* getGeoIP();

    static void setSetting(FriendMapSettings& settings);

private:
    static void init(const RsPlugInInterfaces& interfaces);
    interface(const RsPlugInInterfaces& interfaces);
    const RsPlugInInterfaces interfaces;
    GeoIP* geoip;
    static interface* instance;
};

#endif // INTERFACE_H
