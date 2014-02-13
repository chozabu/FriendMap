!include("../Common/retroshare_plugin.pri"): error("Could not include file ../Common/retroshare_plugin.pri")

TARGET = FriendMap

CONFIG += qt uic qrc resources

HEADERS -= upnp/upnputil.h
SOURCES -= upnp/upnputil.c

win32{
#Fixing libGeoIp compile errors
DEFINES += WINVER=0x0501 _WIN32_WINNT=0x0501 PACKAGE_VERSION=\\\"1.6\\\"

INCLUDEPATH += ../../../geoip-api-c/libGeoIP ../../../marble/include
SOURCES +=   ../../../geoip-api-c/libGeoIP/GeoIp.c ../../../geoip-api-c/libGeoIP/GeoIpCity.c ../../../geoip-api-c/libGeoIP/GeoIP_deprecated.c
LIBS += -lQtSVG4 -lQtWebKit4 -lws2_32
}

RESOURCES += \
    fmimages.qrc

HEADERS += \
    FriendMapPlugin.h \
    FriendMapPage.h \
    MarbleWidget.h \
    PaintLayer.h \
    FriendMapSettings.h \
    FriendMapConfigPage.h \
    FriendMapDetached.h

SOURCES += \
    FriendMapPlugin.cpp \
    FriendMapPage.cpp \
    PaintLayer.cpp \
    FriendMapSettings.cpp \
    FriendMapConfigPage.cpp \
    FriendMapDetached.cpp

win32{
    LIBS += -lmarblewidget
} else {
    LIBS += -lmarblewidget -lGeoIP
}

FORMS += \
    FriendMapPage.ui \
    FriendMapConfigPage.ui \
	FriendMapDetached.ui
