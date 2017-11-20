#include "Scrollbar.h"

Scrollbar::Scrollbar(Window * window)
{
	this->window = window;
}

void Scrollbar::update(void(*updateElements)(int))
{
	updateElements(window->getScrollY());
}