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

These windows compile instructons are untested and written by Gnu/Linux programmers. You may experience problems. Feedback is requested.

####Before You Start
You have to add mingw's path and qmake's path in the environment variable. (use C:\Qt\20xx.xx.x\MinGW\bin and C:\Qt\20xx.xx.x\qt\bin. 
To check that cmake.exe, gcc.exe and qmake.exe are in your %PATH% :

* open a commandline-window (start->run program->cmd)
* run "cmake" , it should give you a help message and show you what compilation options it found
* run "gcc -v" , it should give you version info
* run "qmake" , it should give you help output
* (Hint: make sure not to add the directory %QT-installation-dir%/bin but rather %QT-installation-dir%/qt/bin, there are for some reason incompatible dll's that might lead to crashes)

If one of those command are not known or the path is not set correctly, it may not compile. 

####Marble Install
Install marble from http://marble.kde.org/features.php.
This install all the widgets that are accessed from this plugin.

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

Now, add this line to your plugins.pro: FriendMap \  

At present, skip this step: Build it according to the directions on the website at http://techbase.kde.org/Projects/Marble/WindowsCompiling.

and don't worry about the following, until further testing is done.
<pre>
cd src\lib
pwd
Development\marble\src\lib
cp libmarbelwidget.dll.a ..\..\Development\lib
</pre>

Note: if you are under Windows 7 you must be root to install marble in the standard place. See http://www.howtogeek.com/howto/windows-vista/run-a-command-as-administrator-from-the-windows-vista-run-box/.

#####Clone latest version of FriendMap
Obtain the source code and put into the correct folder:
<pre>
cd Development\RSsourcefolder\plugins\  
git clone git@github.com:chozabu/FriendMap.git  
</pre>

####Build It
The time has now come to rebuild RetroShare using QtCreator. This will rebuild RetroShare, and all of the plugins.

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
