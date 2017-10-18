#include <iostream>
#include <GL\glew.h>

#include "Window.h"

void errorCallback(int32 code, const char message[]);
void windowSizeCallback(GLFWwindow * window, int32 width, int32 height);

Window::Window(int32 width, int32 height, const char title[], bool vSync, bool resizable) {
	init(width, height, title, vSync, resizable);
}

void Window::init(int32 width, int32 height, const char title[], bool vSync, bool resizable) {
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		fprintf(stderr, "Failed to initalize GLFW!");
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, resizable);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (width > 0 && height > 0) {
		window = glfwCreateWindow(width, height, title, 0, 0);
		this->width = width;
		this->height = height;
	}
	else {
		window = glfwCreateWindow(vidMode->width, vidMode->height, title, glfwGetPrimaryMonitor(), 0);
		this->width = vidMode->width;
		this->height = vidMode->height;
	}

	if (!window) {
		fprintf(stderr, "Failed to create window!");
		glfwTerminate();
		exit(-1);
	}
	else if (width > 0 && height > 0)
		glfwSetWindowPos(window, (vidMode->width - width) / 2, (vidMode->height - height) / 2);

	glfwMakeContextCurrent(window);

	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW!");
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(-1);
	}

	glfwSwapInterval(vSync);

	glClearColor(0, 0, 0, 1);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetWindowSizeCallback(window, windowSizeCallback);

	glfwSetWindowUserPointer(window, this);
}

void Window::poll() {
	glfwPollEvents();
}

void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap() {
	glfwSwapBuffers(window);
}

int32 Window::getWidth() {
	return width;
}

int32 Window::getHeight() {
	return height;
}

void Window::setWidth(int32 width) {
	this->width = width;
}

void Window::setHeight(int32 height) {
	this->height = height;
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::close() {
	glfwSetWindowShouldClose(window, false);
}

bool Window::isKeyPressed(int32 key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

Window::~Window() {
	glfwDestroyWindow(window);
}

void Window::terminate() {
	glfwTerminate();
}

void errorCallback(int32 code, const char message[]) {
	fprintf(stderr, "Error code: %d  -  %s", code, message);
}

void windowSizeCallback(GLFWwindow * window, int32 width, int32 height) {
	Window * wObj = static_cast<Window *> (glfwGetWindowUserPointer(window));
	glViewport(0, 0, width, height);
	wObj->setWidth(width);
	wObj->setHeight(height);
}