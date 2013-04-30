#ifndef GAMEMANAGER_H_DEFINED
#define GAMEMANAGER_H_DEFINED

#include "Music.hpp"

class GameManager
{
public:
	GameManager();
	virtual ~GameManager();

	/// The main loop of the game.
	//	Here's where the whole game hangs up.
	void run();

	/// Stores a buffer of input chars and print them onscreen.
	void bufferInput(Buffer* buffer, SDLKey key, Uint16 unicode);

	/// Places #buffer onscreen.
	void bufferPrint(Buffer* buffer);

private:

	/// Current background music
	Music* bgMusic;

	/// Tells if we're gonna quit the game.
	bool willQuit;

};

#endif /* GAMEMANAGER_H_DEFINED */

