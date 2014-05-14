#!/bin/bash

mkdir lemon-tmp
cd lemon-tmp

if ! [ -a lemon-1.3.tar.gz ]
then
    echo "Downloading lemon..."
    wget http://lemon.cs.elte.hu/pub/sources/lemon-1.3.tar.gz
fi

echo "Uncompressing archive..."
tar -xvf lemon-1.3.tar.gz

cd lemon-1.3

function compile {
    cmake ..
    make
}

function check {
    make check
}

function install {
    sudo make install
}

mkdir build
cd build

while true; do
    read -p "Do you want to compile lemon? [y/n] " yn
    case $yn in
        [Yy]* ) compile; break;;
        [Nn]* ) break;;
        * ) echo "Please answer yes or no."
    esac
done

while true; do
    read -p "Do you want to run the checks? [y/n] " yn
    case $yn in
        [Yy]* ) check; break;;
        [Nn]* ) break;;
        * ) echo "Please answer yes or no."
    esac
done

while true; do
    read -p "Do you want to install lemon on the system? [y/n] " yn
    case $yn in
        [Yy]* ) install; break;;
        [Nn]* ) break;;
        * ) echo "Please answer yes or no."
    esac
done

cd ../../..

while true; do
    read -p "Do you want to remove lemon sources? [y/n] " yn
    case $yn in
        [Yy]* ) rm -r lemon-tmp; break;;
        [Nn]* ) break;;
        * ) echo "Please answer yes or no."
    esac
done
