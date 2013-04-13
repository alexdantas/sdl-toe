/// Implementation of the Buffer. Have a nice day

#include "Buffer.hpp"

Buffer::Buffer(int maxSize)
{
	this->buffer  = "";
    this->maxSize = maxSize;
}
Buffer::~Buffer()
{
	// yeah...
}
void Buffer::add(std::string text)
{
    if (this->getLength() + text.length() <= this->maxSize)
		this->buffer += text;
}
void Buffer::addChar(char c)
{
    unsigned int length = this->getLength() + 1;
    
    if (length <= this->maxSize)
		this->buffer += c;
}
std::string Buffer::get()
{
	return this->buffer;
}
void Buffer::backspace(int ammount)
{
    if (ammount >= this->getLength())
		this->clear();
    
	if (!this->buffer.empty())
        this->buffer.erase(this->getLength() - ammount);
}
void Buffer::clear()
{
	this->buffer = "";
}
int Buffer::getLength()
{
    return this->buffer.length();
}

