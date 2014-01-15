##GeoGraphic Friend Map
I don't know who made this plugin. just doing a few minor fixes <br>

###Install
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
