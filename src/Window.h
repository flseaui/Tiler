#ifndef __WINDOW_H_
#define __WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Types.h"

class Window {
public:
	Window(int32 width, int32 height, const char title[], bool vSync, bool resizable);

	void poll();
	void clear();
	void swap();

	int32 getWidth();
	int32 getHeight();
	void setWidth(int32 width);
	void setHeight(int32 height);

	bool shouldClose();
	void close();

	bool isKeyPressed(int32);

	~Window();

	static void terminate();
private:
	GLFWwindow * window;
	int32 width, height;

	void init(int32 width, int32 height, const char title[], bool vSync, bool resizable);
};

#endif
