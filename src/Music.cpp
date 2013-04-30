
#include "Music.hpp"

Music::Music(std::string filepath)
{
    this->music     = NULL;
	this->setMusic(filepath);
    this->load();
}
Music::~Music()
{
	if (this->music) Mix_FreeMusic(this->music);
}
void Music::setMusic(std::string filepath)
{
    this->filepath = filepath;
    this->load();
}
bool Music::play(int times)
{
    if (!this->music)
        return false;

    if (Mix_PlayMusic(this->music, times))
    {
        SDLManager::errorLog("Couldn't play music on " + this->filepath);
        return false;
    }

//  how can I make it call a member function when done? apparently it
//	doesnt work this way
//	Mix_HookMusicFinished(this->finishedPlaying);

    return true;
}
void Music::stop()
{
	SDLManager::stopMusic();
}
void Music::pause()
{
	SDLManager::pauseMusic();
}
void Music::unpause()
{
	SDLManager::resumeMusic();
}
void Music::restart()
{
	this->stop();
    this->play();
}
bool Music::load()
{
	if (this->music) Mix_FreeMusic(this->music);

    this->music = Mix_LoadMUS(this->filepath.c_str());
    if (!this->music)
    {
        SDLManager::errorLog("Music::load: Couldn't load music on " + this->filepath);
        return false;
    }

    return true;
}
// void Music::finishedPlaying()
// {
// 	this->isPlaying = false;
// }
