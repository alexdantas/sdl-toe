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

    /// Loads the font into memory.
    //  This is automatically called when initialized, don't bother
    //  with it.
    //  The only situation on which you might need to call it is when
    //  you call setFont().    
	bool load();

    /// Sets the current font to be the one on #filepath.
    //  @note Must call load()
	void setFont(std::string filepath, int size=12);

    /// Sets the color of the font on RGB
    //  This is applied automatically, no need to call load().
	void setColor(int red=255, int green=255, int blue=255);

    /// Shows #text on positions #x and #y with #style.
    //  @note Keep in mind you must refresh screen after this.
    bool print(int x=0, int y=0, std::string text="normal");
    
    /// Shows #text on positions #x and #y with #style.
    //  @note Keep in mind you must refresh screen after this.
    //  #style can be "bold", "italic", "underline" and "normal"
    bool print(int x, int y, std::string text, std::string style);

    int getW();
    int getH();
    
private:
	std::string  filepath;
	TTF_Font*    font;
	int          size;
	SDL_Color    color;
	SDL_Surface* surface;
};

#endif /* FONT_H_DEFINED */

