/// This file defines a class that implements a simple buffer.
//  It's capable of storing arbitrary-sized chunks of text. You define
//  the maximum size at startup and the rest is pretty trivial.
//  You'll find it's API very intuitive.

#ifndef BUFFER_H_DEFINED
#define BUFFER_H_DEFINED

#include "SDLManager.hpp"
#include <string>

/// Receives and stores an input.
//  Can be used on high-score screens, or pretty much any situation
//  that allows a text to be typed by the player.
class Buffer
{
public:
	Buffer(int maxSize=255);
    
    ~Buffer();

    /// Appends #text to the buffer inside.
    void add(std::string text);

    /// Appends a single char #c to the buffer inside.
    void addChar(char c);
    
    /// Returns the text inside the buffer.
    std::string get();
    
	/// Erases #ammount characters from the current buffer.
	//  Don't worry, if it's bigger than the current size, it'll
    //  erase everything.
    //  @note Don't you dare send this a negative ammount!
    void backspace(int ammount=1);

    /// Completely erases the text inside.
    void clear();

    int getLength();
    
private:
    std::string buffer;
    unsigned int maxSize;
};

#endif /* BUFFER_H_DEFINED */


