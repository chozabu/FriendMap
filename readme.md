##GeoGraphic Friend Map
I don't know who made this plugin. just doing a few minor fixes <br>

###Debian GNU/Linux
####pre-reqs
install libmarble-dev and libgeoip-dev:<br>
sudo apt-get  install libmarble-dev libgeoip-dev<br>
####clone
cd myretrosharetrunk/plugins/ <br>
git clone git@github.com:chozabu/FriendMap.git
####build
cd FriendMap <br>
qmake-qt4 <br>
make <br>
####install
cp libFriendMap.so.1.0.0 ~/.retroshare/extensions <br>
cd ~/.retroshare/extensions <br>
mv libFriendMap.so.1.0.0 libFriendMap.so  <br>
wget http://geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz<br>
gunzip GeoLiteCity.dat.gz <br>
<br>


###Windows
####pre-reqs
LibGeoIP from: https://github.com/maxmind/geoip-api-c/archive/v1.5.1.zip to Development\GeoIP-1.5.1
Build it and copy libGeoIP.a from Development\GeoIP-1.5.1\libGeoIP\.libs\ to Development\lib\

Marble source:
Do it in your Development folder, so the source will be under Development\marble
git clone -b KDE/4.11 git://anongit.kde.org/marble marble
Build it and copy libmarblewidget.dll.a from Development\marble\src\lib\ to Development\lib\

####clone
cd Development\RSsourcefolder\plugins\
git clone git@github.com:chozabu/FriendMap.git

####build
Add this line to your plugins.pro: FriendMap \
Use Qt Creator or the buildscript

####install
Get marble and install it: http://marble.kde.org/install.php
Copy FriendMap.dll from your build output folder to Retroshare\Data\extensions or to %appdata%\RetroShare\extensions
Download http://geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz
Extract GeoLiteCity.dat under Retroshare\Data\extensions or to %appdata%\RetroShare\extensions
Copy libmarblewidget.dll from Development\marble\src\lib\ to your RetroShare folder
Copy the following dlls from Qt\bin to your RetroShare folder:
-QtCore4.dll
-QtDeclarative4.dll
-QtGui4.dll
-QtNetwork4.dll
-QtSvg4.dll
-QtWebKit4.dll
-QtXml4.dll
-QtScript4.dll
-QtSql4.dll
-QtXmlPatterns4.dll
Start RS and set the paths under options-->FriendMap


This product requires GeoLite2 data created by MaxMind, available from
<a href="http://www.maxmind.com">http://www.maxmind.com</a>.
