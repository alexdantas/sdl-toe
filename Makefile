# toe Makefile for Linux

PROGRAM = toe
EXE		= toe
CFLAGS	= -Wall -Wextra -g
LDFLAGS = `sdl-config --cflags --libs` \
		   -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx
OBJ		= obj/SDLManager.o	  obj/main.o			   obj/Sprite.o \
		  obj/Player.o		  obj/Font.o			   obj/Buffer.o \
		  obj/Music.o		  obj/Animation.o		   obj/Timer.o	\
		  obj/Particle.o	  obj/ParticleContainer.o  obj/SFX.o    \
		  obj/VisibleObject.o obj/GameManager.o        obj/ConvertUTF.o

DIRS    = src obj ogg ttf img wav

# Distribution tarball
TARNAME  = $(PROGRAM)
VERSION  = 1.0
DISTDIR  = $(TARNAME)-$(VERSION)
DISTDIRS = $(DISTDIR)/src $(DISTDIR)/obj $(DISTDIR)/ogg \
           $(DISTDIR)/ttf $(DISTDIR)/wav $(DISTDIR)/img

all: $(EXE)
	# Build successful!

$(EXE): $(OBJ)
	# Linking...
	g++ $(OBJ) -o $(EXE) $(LDFLAGS)

obj/ConvertUTF.o: src/ConvertUTF.c
	g++ src/ConvertUTF.c -c -o obj/ConvertUTF.o

obj/%.o: src/%.cpp
	# Compiling $<...
	g++ $(CFLAGS) $< -c -o $@

run: all
	./$(EXE)

clean:
	# Cleaning...
	-rm -f $(EXE) $(OBJ)

dirs:
	@mkdir -p $(DIRS)

dist: clean $(DISTDIR).tar.gz

$(DISTDIR).tar.gz: $(DISTDIR)
	$(MUTE)tar czf $(DISTDIR).tar.gz $(DISTDIR)
	$(MUTE)rm -rf $(DISTDIR)

$(DISTDIR):
	$(MUTE)mkdir -p $(DISTDIRS)
	-$(MUTE)cp * -t $(DISTDIR)
	-$(MUTE)cp -r img/* $(DISTDIR)/img
	-$(MUTE)cp -r ogg/* $(DISTDIR)/ogg
	-$(MUTE)cp -r obj/* $(DISTDIR)/obj
	-$(MUTE)cp -r src/* $(DISTDIR)/src
	-$(MUTE)cp -r ttf/* $(DISTDIR)/ttf
	-$(MUTE)cp -r wav/* $(DISTDIR)/wav

# Uploads results on a website
WEBSITE = alexdantas.net
USER	= alexd075
WEB_DIR = public_html/projects/sdl-toe

up: all clean dist
	# Uploading results to ${WEBSITE}...
	@rsync -avze "ssh -p 2222" $(DISTDIR).tar.gz ${USER}@${WEBSITE}:$(WEB_DIR)

