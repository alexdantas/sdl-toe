# platformer Makefile

CFLAGS  = -Wall -Wextra -g
LDFLAGS = `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf
EXE     = platformer
OBJ     = obj/SDLManager.o obj/main.o obj/Sprite.o \
          obj/Player.o     obj/Font.o

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
	-rm -f $(EXE) $(OBJ)

dirs:
	@mkdir -p obj src