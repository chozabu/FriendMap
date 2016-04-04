!include("../Common/retroshare_plugin.pri"): error("Could not include file ../Common/retroshare_plugin.pri")

TARGET = FriendMap

CONFIG += qt uic qrc resources c++11

HEADERS -= upnp/upnputil.h
SOURCES -= upnp/upnputil.c

greaterThan(QT_MAJOR_VERSION, 4) {
	# Qt 5
	QT += widgets
	LIBS += -lmarblewidget-qt5
}else{
	LIBS += -lmarblewidget
}

win32 {
    DEFINES += _USE_MATH_DEFINES
}

RESOURCES += \
    fmimages.qrc

HEADERS += \
    FriendMapPlugin.h \
    FriendMapPage.h \
    PaintLayer.h \
    FriendMapSettings.h \
    FriendMapConfigPage.h \
    FriendMapDetached.h \
    FriendMapController.h \
    GeoPeer.h \
    PositionManager.h \
    MarbleWidget.h \
    interface.h \
    DataModel.h

SOURCES += \
    FriendMapPlugin.cpp \
    FriendMapPage.cpp \
    PaintLayer.cpp \
    FriendMapSettings.cpp \
    FriendMapConfigPage.cpp \
    FriendMapDetached.cpp \
    FriendMapController.cpp \
    GeoPeer.cpp \
    PositionManager.cpp \
    interface.cpp \
    DataModel.cpp

LIBS += -lGeoIP

FORMS += \
    FriendMapPage.ui \
    FriendMapConfigPage.ui \
	FriendMapDetached.ui
