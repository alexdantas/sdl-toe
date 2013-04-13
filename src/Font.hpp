#ifndef FONT_H_DEFINED
#define FONT_H_DEFINED

#include "SDLManager.hpp"
#include <string>

class Font
{
public:
    /// Initializes pretty much everything.
    //  Yeah, don't bother calling any of the functions below unless
    //  you want to override the font or change it's size.
	Font(std::string filepath, int size);
    
	virtual ~Font();

    /// Loads a font into memory.
    //  Automatically called when initialized, this can be used to
    //  refresh when setFont() is called.
	bool load();

    /// Sets the current font to be the one on #filepath.
    //  @note Must call load()
	void setFont(std::string filepath, int size);

    /// Sets the color of the font on RGB
    //  This is applied automatically, no need to call load().
	void setColor(int red, int green, int blue);

    /// Shows #text on positions #x and #y with #style.
    //  @note Keep in mind you must refresh screen after this.
    bool print(int x, int y, std::string text);
    
    /// Shows #text on positions #x and #y with #style.
    //  @note Keep in mind you must refresh screen after this.
    //  #style can be "bold", "italic", "underline" and "normal"
    bool print(int x, int y, std::string text, std::string style);
    
private:
	std::string  filepath;
	TTF_Font*    font;
	int          size;
	SDL_Color    color;
	SDL_Surface* surface;
};

#endif /* FONT_H_DEFINED */

