#include "Text.h"

Text::Text(const char* text)
{
	content = text;
}

void Text::setContent(const char* content)
{
	this->content = content;
}

const char* Text::getContent()
{
	return content;
}