!include("../Common/retroshare_plugin.pri"): error("Could not include file ../Common/retroshare_plugin.pri")

TARGET = FriendMap

CONFIG += qt uic qrc resources

HEADERS -= upnp/upnputil.h
SOURCES -= upnp/upnputil.c

RESOURCES += \
    fmimages.qrc

HEADERS += \
    FriendMapPlugin.h \
    FriendMapPage.h \
    MarbleWidget.h \
    PaintLayer.h \
    FriendMapSettings.h \
    FriendMapConfigPage.h \
    FriendMapDetached.h \
    FriendMapController.h

SOURCES += \
    FriendMapPlugin.cpp \
    FriendMapPage.cpp \
    PaintLayer.cpp \
    FriendMapSettings.cpp \
    FriendMapConfigPage.cpp \
    FriendMapDetached.cpp \
    FriendMapController.cpp

LIBS += -lmarblewidget -lGeoIP

FORMS += \
    FriendMapPage.ui \
    FriendMapConfigPage.ui \
	FriendMapDetached.ui
