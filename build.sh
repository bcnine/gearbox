#!/bin/bash

OS=`uname -s`

if [ $OS == "MINGW64_NT-10.0" ] 
then

echo "Configuring for Windows..."

# Remove old files to ensure we pick up the latest.
PREFIX=/c/Users/bcollins/b3p
WINPREFIX=/c/Users/bcollins/b3p
rm "$PREFIX/lib/gearbox.lib"

FREEIMAGE_INCLUDE_DIR=$PREFIX/include
FREEIMAGE_LIBRARIES=$PREFIX/lib/FreeImage.lib

COMPILER="Visual Studio 15 2017 Win64"

CXX_FLAGS="/EHsc /Qstd:c++11"

RELEASE_DIR=$WINPREFIX

MAKE_DEBUG_INSTALL="cmake --build . --target install --config Debug"
MAKE_RELEASE_INSTALL="cmake --build . --target install --config Release"

export BUILD_TYPE="Release"

# Unfortunately this is required to tell cmake where the Qt5 config files are. I would
# have thought these would have been distributed with cmake, but they are in fact
# shipped with Qt5.
export CMAKE_PREFIX_PATH="C:\\Qt\\5.12.2\\msvc2017_64"

rm -rf win32
mkdir -p win32
cd win32

elif [ $OS == "Darwin" ]
then

echo "Configuring for Darwin..."

MAKE_INSTALL="make install"
PREFIX="/Users/bcollins/b3p"
RELEASE_DIR=$PREFIX
COMPILER="Unix Makefiles"

CXX_FLAGS="-std=c++0x -stdlib=libc++ -g3 -Wall -O0"

export CMAKE_PREFIX_PATH="/Users/bcollins/Qt/5.5/clang_64"

MAKE_DEBUG_INSTALL="cmake --build . --target install --config Debug"
MAKE_RELEASE_INSTALL="cmake --build . --target install --config Release"

export BUILD_TYPE="Release"

rm -rf darwin
mkdir -p darwin
cd darwin

elif [ $OS == "Linux" ]
then

echo "Configuring for Linux..."
MAKE_INSTALL="make install"
RELEASE_DIR=/home/bcollins/b3p/spartan/1.0.0
COMPILER="Unix Makefiles"

rm -rf linux
mkdir -p linux
cd linux

PREFIX=/usr/
ALT_PREFIX=/home/bcollins/sw
BOOST_DIR=$PREFIX

GLEW_INCLUDE_DIR="$PREFIX/include"
GLEW_LIBRARIES="$PREFIX/lib/x86_64-linux-gnu/libGLEW.so"

SUL_INCLUDE_DIR="$ALT_PREFIX/include"
SUL_LIBRARIES="$ALT_PREFIX/lib/libsul.so"
SUL_DBG_LIBRARIES="$ALT_PREFIX/lib/libsul_dbg.so"

fi

cmake -G "$COMPILER" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DCMAKE_CXX_FLAGS="$CXX_FLAGS" -DCMAKE_INSTALL_PREFIX="$RELEASE_DIR" -DFreeImage_INCLUDE_DIR="$FREEIMAGE_INCLUDE_DIR" -DFreeImage_LIBRARIES="$FREEIMAGE_LIBRARIES" ../source

$MAKE_DEBUG_INSTALL
$MAKE_RELEASE_INSTALL
