
#ifndef BUFFERINPUT_H_DEFINED
#define BUFFERINPUT_H_DEFINED

#include "SDLManager.hpp"
#include <string>

/// Receives and stores an input.
//  Can be used on high-score screens, or pretty much any situation
//  that allows a text to be typed by the player.
class BufferInput
{
public:
	BufferInput();
    ~BufferInput();
    void add(std::string text);
    std::string get();
    void backspace();

private:
    std::string buffer;
}

#endif /* BUFFERINPUT_H_DEFINED */


