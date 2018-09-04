sudo apt-get install vim
sudo apt-get install g++
sudo apt-get install gcc
sudo apt-get install git
sudo apt-get update
cd ./package/redis
sudo tar -xvf redis-4.0.6.tar.gz
cd ./redis-4.0.6
sudo make
sudo mkdir ~/redis
sudo cp src/redis-server src/redis-cli ../redis.conf ~/redis/
cd ./deps/hiredis
sudo make 
sudo make install
sudo apt-get install mysql-server
sudo apt-get install libmysql++-dev
sudo apt-get install make
sudo apt-get install cmake
sudo cd ../../../../
sudo sh ./vim/.vimplus/install.sh
