#ifndef __SCROLLBAR_H_
#define __SCROLLBAR_H_

#include "Window.h";

class Scrollbar
{
public:
	Scrollbar(Window * window);
	void update(void(*updateElements)(int));
private:
	Window * window;
};

#endif