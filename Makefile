# platformer Makefile for Linux

CFLAGS	= -Wall -Wextra -g
LDFLAGS = `sdl-config --cflags --libs` \
		   -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx
EXE		= platformer
OBJ		= obj/SDLManager.o	  obj/main.o			   obj/Sprite.o \
		  obj/Player.o		  obj/Font.o			   obj/Buffer.o \
		  obj/Music.o		  obj/Animation.o		   obj/Timer.o	\
		  obj/Particle.o	  obj/ParticleContainer.o  obj/SFX.o    \
		  obj/VisibleObject.o obj/GameManager.o

all: $(EXE)
	# Build successful!

$(EXE): $(OBJ)
	# Linking...
	g++ $(OBJ) -o $(EXE) $(LDFLAGS)

obj/%.o: src/%.cpp
	# Compiling $<...
	g++ $(CFLAGS) $< -c -o $@

run: all
	./$(EXE)

clean:
	# Cleaning...
	-rm -f $(EXE) $(OBJ)

dirs:
	@mkdir -p obj src

# Distribution tarball
TARNAME = platformer
VERSION = 1.0
DISTDIR = $(TARNAME)-$(VERSION)

dist: clean $(DISTDIR).tar.gz

$(DISTDIR).tar.gz: $(DISTDIR)
	$(MUTE)tar czf $(DISTDIR).tar.gz $(DISTDIR)
	$(MUTE)rm -rf $(DISTDIR)
	$(MUTE)cp $(DISTDIR).tar.gz ..
	$(MUTE)rm -f $(DISTDIR).tar.gz

$(DISTDIR):
	$(MUTE)mkdir -p $(DISTDIR)/src $(DISTDIR)/ogg
	$(MUTE)mkdir -p $(DISTDIR)/img $(DISTDIR)/obj
	$(MUTE)mkdir -p $(DISTDIR)/ttf
	-$(MUTE)cp * -t $(DISTDIR)
	-$(MUTE)cp -r img/* $(DISTDIR)/img
	-$(MUTE)cp -r ogg/* $(DISTDIR)/ogg
	-$(MUTE)cp -r obj/* $(DISTDIR)/obj
	-$(MUTE)cp -r src/* $(DISTDIR)/src
	-$(MUTE)cp -r ttf/* $(DISTDIR)/ttf

# Uploads results on a website
WEBSITE = alexdantas.net
USER	= alexd075
WEB_DIR = public_html/projects/platformer

up: all
	# Uploading results to ${WEBSITE}...
	@rsync -avze "ssh -p 2222" ../$(DISTDIR) ${USER}@${WEBSITE}:$(WEB_DIR)
	# Removing /tmp dirs
	@rm -rf $(FILESDIR)

