#include "Layer.h"

bool Layer::enabled()
{
	return enabled;
}

void Layer::setEnabled(bool state)
{
	enabled = state;
}

const char* Layer::getTitle()
{
	return title;
}

void Layer::setTitle(const char* title)
{
	this->title = title;
}