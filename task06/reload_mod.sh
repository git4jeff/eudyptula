# !/bin/sh

make
sudo rmmod hello
sudo insmod hello.ko
sudo chmod 666 /dev/eudyptula

echo "cat /dev/eudyptula"
sudo cat /dev/eudyptula

echo

echo "echo -n nonsense > /dev/eudyptula"
sudo echo -n nonsense > /dev/eudyptula

echo "echo -n 09b0d224b5bb > /dev/eudyptula"
sudo echo -n 09b0d224b5bb > /dev/eudyptula

