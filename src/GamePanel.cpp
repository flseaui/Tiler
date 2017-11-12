#include "GamePanel.h"
#include <iostream>

GamePanel::GamePanel(Window * window, Camera * camera) : Panel(window, camera) {
	state = 0;
	this->window = window;
	this->camera = camera;
	//line = new ColRect(camera, 1, 1, 1, 1, 0, 0, 0, 100, 0.1f);
	canvas = new Canvas(window, camera, 16, 16, 32, 32);
	//tool buttons
	toolButtons[0] = new TexButton(window, camera, "res/textures/eraser.png", 0, 0, 32, 32, 0, true);
	toolButtons[1] = new TexButton(window, camera, "res/textures/paint_bucket.png", 0, 32, 32, 32, 1, true);
	//tile buttons
	tileButtons[0] = new TexButton(window, camera, "res/textures/sky_tile.png", 0, 64, 32, 32, 1, true);
	tileButtons[1] = new TexButton(window, camera, "res/textures/stone_tile.png", 0, 96, 32, 32, 2, true);
	tileButtons[2] = new TexButton(window, camera, "res/textures/cmbt.png", 0, 128, 32, 32, 3, true);
	tileButtons[3] = new TexButton(window, camera, "res/textures/clab.png", 0, 160, 32, 32, 4, true);

	panels[0] = new ColRect(camera, 0, 0, 1, 1, 0, 0, 0, window->getWidth() / 8, window->getHeight(), false);
	panels[1] = new ColRect(camera, 1, 0, 0, 1, window->getWidth(), 0, 0, window->getWidth() / 8, window->getHeight(), false);
	curTile = 0;
}

void GamePanel::update() {
	canvas->update(curTile);

	for (TexButton* button : toolButtons)
	{
		button->update();
		if (button->getState() == 2)
		{
			for (TexButton* otherButton : toolButtons)
				if (otherButton != button)
					otherButton->setState(0);

				curTile = button->getID();
		}
		//if button is paint bucket
		if (button->getID() == 1)
			canvas->setBucket(button->getState() == 2 ? true : false);
	}

	for (TexButton* button : tileButtons)
	{
		button->update();
		if (button->getState() == 2)
		{
			for (TexButton* otherButton : tileButtons)
				if (otherButton != button)
					otherButton->setState(0);
				curTile = button->getID();
		}
	}
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
	for (TexButton* button : toolButtons)
	{
		button->renderTexture();
		button->render();
	}
	for (TexButton* button : tileButtons)
	{
		button->renderTexture();
		button->render();
	}
	for (ColRect* panel : panels)
		panel->render();
	canvas->render();
}

void GamePanel::setActive()
{
	state = 0;
}

GamePanel::~GamePanel() {
}