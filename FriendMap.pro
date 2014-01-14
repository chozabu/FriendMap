!include("../Common/retroshare_plugin.pri"): error("Could not include file ../Common/retroshare_plugin.pri")

TARGET = FriendMap

CONFIG += qt uic qrc resources

HEADERS -= upnp/upnputil.h
SOURCES -= upnp/upnputil.c

win32{
INCLUDEPATH += ../../../GeoIP-1.5.1/libGeoIP ../../../marble/include
SOURCES +=   ../../../GeoIP-1.5.1/libGeoIP/GeoIp.c ../../../GeoIP-1.5.1/libGeoIP/GeoIpCity.c
LIBS += -lQtSVG4 -lQtWebKit4 -lws2_32
}

RESOURCES += images.qrc

HEADERS += \
    FriendMapPlugin.h \
    FriendMapPage.h \
    MarbleWidget.h \
    PaintLayer.h \
    FriendMapSettings.h \
    FriendMapConfigPage.h

SOURCES += \
    FriendMapPlugin.cpp \
    FriendMapPage.cpp \
    PaintLayer.cpp \
    FriendMapSettings.cpp \
    FriendMapConfigPage.cpp

LIBS += -lmarblewidget -lGeoIP

FORMS += \
    FriendMapPage.ui \
    FriendMapConfigPage.ui
