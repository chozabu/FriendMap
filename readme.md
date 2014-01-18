##GeoGraphic Friend Map
Original Author: Nyfor.

This is an experimental plugin.

Changes include:
 - Update to work with latest RS
 - Fix Crashes
 - Show Friend links
 - Nicer Map
 - Cache Data
 - toggles for friend links, clouds, citys, borders, etc
 - persistant settings

###Debian GNU/Linux
####Dependencies
Install libmarble-dev and libgeoip-dev:  
<pre>
sudo apt-get  install libmarble-dev libgeoip-dev
</pre>

####Clone From Github
Obtain the source code into the appropriate folder:
<pre>
cd myretrosharetrunk/plugins/  
git clone git@github.com:chozabu/FriendMap.git
</pre>

####Build
If you can build the RetroShare source, you will understand and be successful.
<pre>
cd FriendMap  
qmake  
make  
</pre>

Note: on some Gnu/Linux versions, you may have to type qmake-qt4 instead of qmake.

####Install
The following copies the library to the default location:
<pre>
cp libFriendMap.so.1.0.0 ~/.retroshare/extensions  
cd ~/.retroshare/extensions  
mv libFriendMap.so.1.0.0 libFriendMap.so  
</pre>

Now get the required mapping data:
<pre>
wget http://geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz  
gunzip GeoLiteCity.dat.gz  
</pre>  
  

###Windows
'Let the games begin'

####Dependencies
LibGeoIP from: https://github.com/maxmind/geoip-api-c/archive/v1.5.1.zip to Development\GeoIP-1.5.1  
Build it and copy libGeoIP.a from Development\GeoIP-1.5.1\libGeoIP\.libs\ to Development\lib\  
  
Marble source:  
Do it in your Development folder, so the source will be under Development\marble  
<pre>
git clone -b KDE/4.11 git://anongit.kde.org/marble marble  
</pre>
Build it and copy libmarblewidget.dll.a from Development\marble\src\lib\ to Development\lib\  

For more information on how to compile marble for windows, please refer to http://techbase.kde.org/Projects/Marble/WindowsCompiling.

Note: if you are under Windows seven you must be root to install marble in the standard place. See http://www.howtogeek.com/howto/windows-vista/run-a-command-as-administrator-from-the-windows-vista-run-box/.

####Clone
Obtain the source code and put into the correct folder:
<pre>
cd Development\RSsourcefolder\plugins\  
git clone git@github.com:chozabu/FriendMap.git  
</pre>

####Build
Add this line to your plugins.pro: FriendMap \  
Use QtCreator or the buildscript to build the .dll

####Install
* Get marble and install it: http://marble.kde.org/install.php
* Copy FriendMap.dll from your build output folder to Retroshare\Data\extensions or to %appdata%\RetroShare\extensions  
* Download http://geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz  
* Extract GeoLiteCity.dat under Retroshare\Data\extensions or to %appdata%\RetroShare\extensions  
* Copy libmarblewidget.dll from Development\marble\src\lib\ to your RetroShare folder  
* Copy the following dlls from Qt\bin to your RetroShare folder:  
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
