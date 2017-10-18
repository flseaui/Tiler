#include "GamePanel.h"

GamePanel::GamePanel(Window * window, Camera * camera) : Panel(window, camera) {
	state = 0;
	this->window = window;
	this->camera = camera;
	line = new ColRect(camera, 1, 1, 1, 1, 0, 0, 0, 100, 0.1f);
}

void GamePanel::update() {
	if (window->isKeyPressed(GLFW_KEY_LEFT))
		camera->translate(glm::vec3(-3, 0, 0));
	if (window->isKeyPressed(GLFW_KEY_RIGHT))
		camera->translate(glm::vec3(3, 0, 0));
	if (window->isKeyPressed(GLFW_KEY_UP))
		camera->translate(glm::vec3(0, -3, 0));
	if (window->isKeyPressed(GLFW_KEY_DOWN))
		camera->translate(glm::vec3(0, 3, 0));
	if (window->isKeyPressed(GLFW_KEY_N))
		camera->zoomi();
	if (window->isKeyPressed(GLFW_KEY_M))
		camera->zoomo();
}

void GamePanel::render() {
	line->render();
}

void GamePanel::setActive()
{
	state = 0;
}

GamePanel::~GamePanel() {
}