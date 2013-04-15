#!/usr/bin/env bash
#
# SDL Cross-Build Download Script v 1.0
# =====================================
# (c) 2006 Dana Olson <dolson@icculus.org>
# Updated 20080617 by Saul D.
#
# SDL 1.2 - http://www.libsdl.org/download-1.2.php
# SDL_image - http://www.libsdl.org/projects/SDL_image/
# SDL_mixer - http://www.libsdl.org/projects/SDL_mixer/
# SDL_net - http://www.libsdl.org/projects/SDL_net/
# SDL_ttf - http://www.libsdl.org/projects/SDL_ttf/

# Path to install to. Default is /opt/SDL-1.2.13
INSTPATH=$1
if [ "$1" == "" ] ; then
	INSTPATH=/opt/SDL-1.2.13
        echo Install path not specified\; using default.
fi

# Check and warn if destination exists.
if [ -e "$INSTPATH" ] ; then
  echo WARNING!!! Install path already exists!
fi

# Allow user to confirm install.
echo SDL libraries will be installed to $INSTPATH.
echo Press Enter to continue, ^C to abort.
read junk

# Create the patch and subdirectory.
mkdir -p $INSTPATH/archives/

# Make sure the directory could be created.
if [ ! -e "$INSTPATH/archives" ] ; then
  echo Couldn\'t create install path. Aborting.
  exit 1
fi
echo Installing...

# Download the SDL archives. Add to this list if you want more libraries.
cd $INSTPATH/archives/
for i in \
http://www.libsdl.org/release/SDL-devel-1.2.13-mingw32.tar.gz \
http://www.libsdl.org/projects/SDL_image/release/SDL_image-devel-1.2.6-VC8.zip \
http://www.libsdl.org/projects/SDL_mixer/release/SDL_mixer-devel-1.2.8-VC8.zip \
http://www.libsdl.org/projects/SDL_net/release/SDL_net-devel-1.2.7-VC8.zip \
http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-devel-2.0.9-VC8.zip
  do wget -c $i
done
cd ..

# Extract the main SDL archive.
tar zxf archives/SDL-devel-1.2.13-mingw32.tar.gz

# Extract the addon archives.
for i in archives/*.zip
  do unzip $i
done

# Make a directory to hold the SDL runtime for Win32.
mkdir SDL-1.2.13/runtime/

# Move all the DLLs and README file into here.
mv */*/*.dll SDL-1.2.13/runtime/
mv SDL-1.2.13/README-SDL.txt SDL-1.2.13/runtime/

# Move all the addon libraries into the lib dir.
mv SDL_*/*/*.lib SDL-1.2.13/lib/

# Move all the addon headers into the include dir.
mv SDL_*/*/*.h SDL-1.2.13/include/

# Remove unneeded directories.
rm -rf SDL_*/

# Make a symlink, so that the sdl-config can be found.
cd SDL-1.2.13/bin/
ln -s sdl-config i586-mingw32msvc-sdl-config

# Patch the sdl-config script to point to install path.
echo "--- i586-mingw32msvc-sdl-config" > sdlcfgfix.patch
echo "+++ i586-mingw32msvc-sdl-config.fix" >> sdlcfgfix.patch
echo "@@ -1,6 +1,6 @@" >> sdlcfgfix.patch
echo " #!/bin/sh" >> sdlcfgfix.patch
echo " " >> sdlcfgfix.patch
echo "-prefix=/Users/hercules/tmp/SDL-1.2.13" >> sdlcfgfix.patch
echo "+prefix=$INSTPATH" >> sdlcfgfix.patch
echo " exec_prefix=\${prefix}" >> sdlcfgfix.patch
echo " exec_prefix_set=no" >> sdlcfgfix.patch
echo " " >> sdlcfgfix.patch
patch < sdlcfgfix.patch
mv sdlcfgfix.patch ../../archives/

# Set proper permissions on some files.
cd ../../
chmod -x SDL-1.2.13/lib/* SDL-1.2.13/runtime/*

# Move everything into install dir.
mv SDL-1.2.13/ tempsdlinstalldir129
mv tempsdlinstalldir129/* ./
rm -r tempsdlinstalldir129/

# Done!
echo
echo Everything is done! SDL was installed in $INSTPATH.
echo This line should work to cross-compile:
echo PATH=$INSTPATH/bin:\$PATH ./configure --target=i586-mingw32msvc --host=i586-mingw32msvc --build=i586-linux
echo
exit 0
