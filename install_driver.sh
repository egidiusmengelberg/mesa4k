#!/bin/bash
processor=$(uname -p)

if [ "${processor}" = "unknown" ] 
then
    echo "Unable to get processor type. Please install driver manually"
    return 1

elif [ "${processor}" = "x86_64" ] 
then
    echo "Detected a 64-bit processor. Installing 64-bit version of libmesasr"
    dpkg -i driver/libmesasr-dev-1.0.14-706.amd64.deb
    apt-get install -f

elif [ "${processor}" = "i686" ] 
then
    echo "Detected a 32-bit processor. Installing 32-bit version of libmesasr"
    dpkg -i driver/libmesasr-dev-1.0.14-706.i386.deb
    apt-get install -f
fi

echo "Succesfully installed driver"