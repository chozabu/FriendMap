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

This product requires GeoLite2 data created by MaxMind, available from <a href="http://www.maxmind.com">http://www.maxmind.com</a>.

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
Note: on some Gnu/Linux versions, you may have to type qmake instead of qmake-qt4.
<pre>
cd FriendMap  
qmake-qt4  
make clean
make  
</pre>


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

It is assumed that you have similar folder structure described in the Retroshare Windows compile instructions, and also that you have Retroshare build enviroment setted up.  

Refer to this page for further instructions: https://wiki.cavebeat.org/index.php/Compile_windows.

It is assumed your RetroShare development folder is under c:\Development and RetroShare's sourcecode is under c:\Development\src  .

It is assumed RetroShare is installed under c:\Program Files (x86)\RetroShare

You will need a bash terminal with cmake, gcc and Qt in your path:

* Refer section "Setup build enviroment"  
* Start devenv.bat (described in section "Make a script to launch your development environment") or MinGW-Shell.bat (if you have the buildscripts). It is possible that some commands need administrator privileges, so start the script by right click on the bat file and select Run as administrator.
* Run the test described in section "Test if everything is working", if one of this test fails, you may have compile problems. 

You will need a Git client:

* MSysGit for command line interface: http://msysgit.github.io/
* TortoiseGit for graphical interface: https://code.google.com/p/tortoisegit/
* Or any other Git client

####LibGeoIP
GeoIP is a C library that enables the user to find geographical and network information of an IP address. To use this library, you may download our free GeoLite Country or City databases. These are updated at the beginning of every month.

#####Get the source
Checkout the source code under c:\Development\geoip-api-c from https://github.com/maxmind/geoip-api-c.git   
Using command line:
<pre>
cd c:\Development
git clone https://github.com/maxmind/geoip-api-c.git
</pre>

Building libGeoIp is problematic, but we don't need the lib, the source files are enough.

####Marble
To read more about some of the features of marble, visit http://marble.kde.org/features.php .

#####Get the source
Checkout the source code under c:\Development\marble from git://anongit.kde.org/marble , branch KDE/4.11 .
Using command line:
<pre>
cd c:\Development
git clone -b KDE/4.11 git://anongit.kde.org/marble marble
cd marble
</pre>

#####Build and install
Marble will be installed under c:\Program Files (x86)\marble\ or c:\Program Files\marble\ by default, you can change the install path by changing the parameters of the cmake.  

For more information visit http://techbase.kde.org/Projects/Marble/WindowsCompiling

Start devenv.bat or MinGW-Shell.bat with administrator privileges, and run these commands:
<pre>
cd c:/Development/marble
mkdir build
cd build
cmake -G "MSYS Makefiles" -DQTONLY=ON -DCMAKE_BUILD_TYPE=Release -DWITH_DESIGNER_PLUGIN=ON ..
make
make install
</pre>

#####Locating Files
Put some files from Marble to the right place in order to make FriendMap compile
* Copy libmarblewidget.dll.a from c:\Development\marble\build\src\lib\ to c:\Development\lib\
* Copy include folder from c:\Program Files (x86)\marble\include\ to c:\Development\marble\include\

####FriendMap plugin
#####Get the source
Checkout the source code under c:\Development\src\plugins from git@github.com:chozabu/FriendMap.git
Using command line:
<pre>
cd c:\Development\src\plugins  
git clone git@github.com:chozabu/FriendMap.git  
</pre>

#####Build
Open the file c:\Development\git\plugins\plugins.pro in text editor and add this line:
<pre>
FriendMap \
</pre>

To build the plugin use the build script, or you can use the Qt Creator.   
If you are using Qt Creator, open the retroshare.pro, not the FriendMap.pro. With Qt Creator you can rebuild only this plugin, if you have built the other RetroShare components before.

#####Install the plugin

To install correctly, complete the following steps:

* Copy FriendMap.dll from c:\Development\build...\plugins\FriendMap\release to Retroshare\Data\extensions (portable) or to %appdata%\RetroShare\extensions  
* Download http://geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz  
* Extract GeoLiteCity.dat under Retroshare\Data\extensions (portable) or to %appdata%\RetroShare\extensions  
* Copy libmarblewidget.dll from c:\Development\marble\build\src\lib\ to c:\Program Files (x86)\RetroShare\  
* Copy the following dlls from c:\Qt\4.8.5\bin\ to c:\Program Files (x86)\RetroShare\:  
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

Finally start RetroShare, at the first time it will be slow.

You may have to set the correct paths under options->FriendMap.

####For distributors
FriendMap plugin needs data and plugins from Marble. Please include instructions for installing standalone Marble.  
Or you can distribute the required Marble files along with this plugin:  

* Make a folder called "marble" under RetroShare folder
* Copy folder from c:\Program Files (x86)\marble\data to RetroShare\marble\data
* Copy folder from c:\Program Files (x86)\marble\plugins to RetroShare\marble\plugins
* marble.exe and other files are not needed
