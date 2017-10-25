#include "GamePanel.h"

GamePanel::GamePanel(Window * window, Camera * camera) : Panel(window, camera) {
	state = 0;
	this->window = window;
	this->camera = camera;
	//line = new ColRect(camera, 1, 1, 1, 1, 0, 0, 0, 100, 0.1f);
	canvas = new Canvas(window, camera, 10, 10, 32, 32);
	buttons[0] = new TexButton(window, camera, "res/textures/cmbt.png", 0, 0, 32, 32);
	buttons[1] = new TexButton(window, camera, "res/textures/stone_tile.png", 0, 32, 32, 32);
	buttons[2] = new TexButton(window, camera, "res/textures/test.png", 0, 64, 32, 32);
}

void GamePanel::update() {
	canvas->update();
	for (TexButton* button : buttons)
		button->update();
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

void GamePanel::render() 
{
	for (TexButton* button : buttons)
	{
		button->renderTexture();
		button->render();
	}
	canvas->render();
}

void GamePanel::setActive()
{
	state = 0;
}

GamePanel::~GamePanel() {
}