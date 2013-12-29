
#include "GameManager.hpp"
#include "SDLManager.hpp"
#include "Font.hpp"
#include "Player.hpp"
#include "Music.hpp"
#include "Timer.hpp"
#include "ParticleContainer.hpp"
#include "SFX.hpp"

GameManager::GameManager()
{
	this->bgMusic = NULL;
}
GameManager::~GameManager()
{
	if (this->bgMusic) delete this->bgMusic;
}
void GameManager::run()
{
	Font font("ttf/UbuntuMono.ttf", 20);
	font.setColor(0, 0, 0);

	this->bgMusic = new Music("ogg/espaguete.ogg");
	this->bgMusic->play();

	SFX sfx1("wav/jump.wav");
	SFX sfx2("wav/powerup.wav");
	SFX sfx3("wav/coin.wav");

    Player currentPlayer = ONE;
    this->reset();

	while (!this->willQuit)
	{
		SDL_Event event;

		// INPUT
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					this->willQuit = true;
					break;
//				case SDLK_p:
//					this->bgMusic->pause();
//					break;
//				case SDLK_r:
//					this->bgMusic->unpause();
//					break;

				default: break;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

                if (SDLManager::isInsideGrid(mouseX, mouseY))
					if (SDLManager::isValidCell(mouseX, mouseY))
                    {
						int i = SDLManager::getIndexX(mouseX);
						int j = SDLManager::getIndexY(mouseY);

                        if (currentPlayer == ONE)
                        {
							this->setCell(i, j, GameManager::X);
                            currentPlayer = TWO;
                            sfx1.play();
                        }
                        else
                        {
                            this->setCell(i, j, GameManager::O);
                            currentPlayer = ONE;
                            sfx2.play();
                        }
                    }

                if (SDLManager::isInsideResetButton(mouseX, mouseY))
                {
                    this->reset();
                    sfx3.play();
                }
			}
			if (event.type == SDL_QUIT)
				this->willQuit = true;
		}

		SDLManager::clearScreen();
        SDLManager::renderBackground();
		this->renderGrid();

		font.print(10, 330, "SDL-toe, by-kure");
        if (currentPlayer == ONE)
			font.print(200, 330, "(X's turn)");
        else
            font.print(200, 330, "(O's turn)");

		SDLManager::refreshScreen();
		SDLManager::framerateWait();
	}
}
void GameManager::reset()
{
	for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
			this->setCell(i, j);
}
void GameManager::renderGrid()
{
	for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
			if (this->grid[i][j] == X)
                SDLManager::renderX(i, j);
            else if (this->grid[i][j] == O)
                SDLManager::renderO(i, j);
        }
}
void GameManager::setCell(int i, int j, GridType type)
{
	this->grid[i][j] = type;
}
