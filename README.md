# sdl-platformer README #

This is a simple platformer game. It's a test project to learn how to program
with SDL.

It's basically a lot of SDL funcionality wrapped up by several helper classes.
They're very modular, so you can take any of them and plug in your project
without worrying too much.

I tried to keep them very commented and with a simple API, so anybody could use
them without too much fuzz.

Someday I plan to make a tutorial-like step-by-step guide on how I made this
game. For now you'll have to go though the Git history (or just look at the
classes, they're not that hard to understand).

## Building ##

Just do the thing you're very used to do.

	$ make
    $ make run

## Windows ##

Yeah, I added support for cross-compiling for Windows. What it means is that you
can sit confortably on your Linux-based OS, while compiling for those stinky
Windows systems.

	$ make -f Makefile.windows
    $ cp -a windows/ your-pendrive/

Then you can send the result to your not-so-tech-savvy friend, who'll just click
the .exe without thinking twice. He'll have the same experience you're having,
so don't worry.

## Dependences ##

	SDL, SDL_Image, SDL_TTF, SDL_Mixer

