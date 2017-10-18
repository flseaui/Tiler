#include "Panel.h"

Panel::Panel(Window* window, Camera* camera) {
	this->window = window;
	this->camera = camera;
}

int Panel::getState()
{
	return state;
}
