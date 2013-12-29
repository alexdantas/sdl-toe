#ifndef GAMEMANAGER_H_DEFINED
#define GAMEMANAGER_H_DEFINED

#include "Music.hpp"

class GameManager
{
public:
	GameManager();
	virtual ~GameManager();

    enum GridType { NONE=0, X, O };
	enum Player { ONE=0, TWO };

	/// The main loop of the game.
	//	Here's where the whole game hangs up.
	void run();

    void reset();

    void renderGrid();
	void setCell(int i, int j, GridType type=NONE);

private:

	/// Current background music
	Music* bgMusic;

	/// Tells if we're gonna quit the game.
	bool willQuit;

    /// The logic state of the grids on the game.
    GridType grid[3][3];
};

#endif /* GAMEMANAGER_H_DEFINED */

