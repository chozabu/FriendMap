##GeoGraphic Friend Map
This extension for retroshare will show your friends on a map or globe.

Original Author: Nyfor.

Chozabus Updates include:
 - Update to work with latest RS
 - Fix Crashes
 - Show Friend links
 - Choice of several map
 - Cache Data
 - optional friend links, clouds, citys, borders, avatars, etc
 - persistant settings  

####Before attempting to build this plugin, you must build the main retroshare project and it's plugins

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

It is assumed that you have the following folder structure, and are using the CLI (command line interface).
<pre>
cd Development
mkdir GeoIP-1.5.1
mkdir marble
</pre>

#####LibGeoIP
GeoIP is a C library that enables the user to find geographical and network information of an IP address. To use this library, you may download our free GeoLite Country or City databases. These are updated at the beginning of every month.

As an older version is required, it must be obtained from the archives. 

Using your browser, visit https://github.com/maxmind/geoip-api-c/archive/v1.5.1.zip and save the file to Development\GeoIP-1.5.1 (the folder previously made.

Following the instructions on the website https://github.com/maxmind/geoip-api-c, build libGeoIP.a.
<pre>
cd GeoIP-1.5.1
cp libGeoIP.a ..\Development\lib
</pre>

#####Marble source  
To read more about some of the features of marble, visit http://marble.kde.org/features.php.

The source to marble libaries are reguired, and it must be installed in the appropriate place, so ensure you are in Development folder  
<pre>
pwd
Development
git clone -b KDE/4.11 git://anongit.kde.org/marble marble
cd marble
</pre>

Build it according to the directions on the website.
For more information on how to compile marble for windows, please refer to http://techbase.kde.org/Projects/Marble/WindowsCompiling.

<pre>
cd src\lib
pwd
Development\marble\src\lib
cp libmarbelwidget.dll.a ..\..\Development\lib
</pre>

Note: if you are under Windows seven you must be root to install marble in the standard place. See http://www.howtogeek.com/howto/windows-vista/run-a-command-as-administrator-from-the-windows-vista-run-box/.

#####Clone latest version of FriendMap
Obtain the source code and put into the correct folder:
<pre>
cd Development\RSsourcefolder\plugins\  
git clone git@github.com:chozabu/FriendMap.git  
</pre>

Now, add this line to your plugins.pro: FriendMap \  

Use QtCreator or the buildscript to build the .dll

####Install FriendMap Plugin
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
