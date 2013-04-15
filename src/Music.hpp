/// @file Music.hpp Handles music-playing
//
//  You can load and play a music.

#ifndef MUSIC_H_DEFINED
#define MUSIC_H_DEFINED

#include "SDLManager.hpp"

class Music
{
public:
    /// Initializes pretty much everything.
    //  Yeah, don't bother calling any of the functions below unless
    //  you want to override the music filepath.
    Music(std::string filepath);

    virtual ~Music();

    /// Loads the music into memory.
    //  This is automatically called when initialized, don't bother
    //  with it.
    //  The only situation on which you might need to call it is when
    //  you call setMusic().
    bool load();

    /// Sets the current music to be the one on #filepath.
    //  @note Must call load()
    void setMusic(std::string filepath);

    /// Plays the loaded music.
    //  @param times How many times we'll play the music. If -1,
    //  infinite loop.
    bool play(int times=-1);

    // The problem with Mix's API is that when I tell it to
    // stop playing music, it stops all musics currently playing
    //void stop();

    /// This function's called automatically when the music stops.
    //  It warns internally that the music has stopped.
    //  @note Don't you dare call it! False alarms are not welcome.
    //
    //  BUG: Mix doesn't allow you to define a callback liek this.
    //       what should I do?
    //void finishedPlaying();

private:
    Mix_Music*  music;
    std::string filepath;
    bool        isPlaying;
};

#endif /* MUSIC_H_DEFINED */
