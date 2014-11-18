#!/bin/bash

echo "Your home path is: " $HOME
cd $HOME/Overlapit/build-Merge-Desktop_Qt_5_3_GCC_32bit-Release
make
cp ./Merge ../Overlapit
cd $HOME/Overlapit/build-mainWindow-Desktop_Qt_5_3_GCC_32bit-Release
make
cp ./mainWindow ../mainWindow
g++ $HOME/Overlapit/check.cpp -o $HOME/Overlapit/check
cp $HOME/Overlapit/check ~/check
cp $HOME/Overlapit/stylesheet.qss ~/stylesheet.qss
cp $HOME/Overlapit/logo.png ~/logo.png
