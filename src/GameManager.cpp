
#include "GameManager.hpp"
#include "SDLManager.hpp"
#include "Font.hpp"
#include "Player.hpp"
#include "Music.hpp"
#include "Timer.hpp"
#include "ParticleContainer.hpp"
#include "IniParser.hpp"
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
	Player player(30, 200);

	Font font("ttf/UbuntuMono.ttf", 20);

	this->bgMusic = new Music("ogg/mmx-intro.ogg");
	this->bgMusic->play();

	Timer timer;
	Timer timer2; timer2.start();

	Buffer buffer;

    SFX coin("wav/coin.wav");
    SFX explosion("wav/explosion.wav");
    SFX jump("wav/jump.wav");
    SFX hit("wav/hit.wav");
    SFX powerup("wav/powerup.wav");

//	ParticleContainer particles("img/jumping-left.png");
//	particles.addParticle(5, 3);
//	particles.addParticle(100, 200);

// testing INI parser

	while (!this->willQuit)
	{
		SDL_Event event;

		timer.start();

		// INPUT
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				bufferInput(&buffer, event.key.keysym.sym, event.key.keysym.unicode);
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					this->willQuit = true;
					break;
				case SDLK_p:
					this->bgMusic->pause();
					timer2.pause();
					break;
				case SDLK_r:
					this->bgMusic->unpause();
					timer2.unpause();
					break;
				case SDLK_s:
					this->bgMusic->stop();
					timer2.stop();
					break;
				case SDLK_n:
                    font.setFont("ttf/Terminus.ttf", 20);
					break;
                case SDLK_d:
                    player.changeAnimation(Player::WALKING_RIGHT);
                    break;
                case SDLK_a:
                    player.changeAnimation(Player::WALKING_LEFT);
                    break;
                case SDLK_w:
                    player.changeAnimation(Player::JUMPING_RIGHT);
                    break;

                case SDLK_1: coin.play(); break;
                case SDLK_2: explosion.play(); break;
                case SDLK_3: jump.play(); break;
                case SDLK_4: hit.play(); break;
                case SDLK_5: powerup.play(); break;

				default: break;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				// do something with the mouse position
			}
			if (event.type == SDL_QUIT)
				this->willQuit = true;
		}

		// LOGIC
		player.update();

		// RENDER
		SDLManager::clearScreen();

		font.print(0, 0,   "Teste Maravilhoso de SDL");
		font.print(0, 20,  "p: pausa musica e timer");
		font.print(0, 40,  "r: continua musica e timer");
		font.print(0, 60,  "s: para musica e timer");
		font.print(0, 80,  "n: muda a fonte");
		font.print(0, 100, "n: muda a fonte");
		font.print(0, 120, "1-9: toca sound effects");
		font.print(0, 140, "Digite algumas teclas...");

		// Show delta onscreen
		static std::stringstream showDelta;
		showDelta.str("");
		showDelta << "Frame delta: " <<  SDLManager::getDelta() << " ms";
		font.print(0, 400, showDelta.str().c_str());

		// Show timer onscreen
		static std::stringstream showTimer;
		showTimer.str("");
		showTimer << "Timer: " << timer2.delta_s() << ":" << timer2.delta_ms() << " ms";
		font.print(0, 420, showTimer.str().c_str());

//		font.print(0, (this->screenH)/2, buffer.get().c_str());
		font.print(0, (600)/2, buffer.get().c_str());

		player.show();
//		particles.show();

		SDLManager::refreshScreen();

		// Let's wait a while if the framerate is too low.
		SDLManager::framerateWait();
	}
}
void GameManager::bufferInput(Buffer* buffer, SDLKey key, Uint16 unicode)
{
	static Font font("ttf/Terminus.ttf", 24);

	if (key == SDLK_BACKSPACE)
		buffer->backspace();

	else if (key == SDLK_RETURN)
		buffer->clear();

	else
	{
		if (SDLManager::isPrintable(key))
		{
			char c = unicode;
			buffer->addChar(c);
		}
	}
}


