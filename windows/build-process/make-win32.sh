#!/bin/sh
make clean
PATH=/opt/SDL-1.2.9/bin:$PATH ./configure --target=i586-mingw32msvc --host=i586-mingw32msvc --build=i386-linux
make
