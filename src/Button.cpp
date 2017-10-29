#include "Button.h"

Button::Button(Window* window, Camera* camera, const char* pPressed, const char* pUnpressed, const char* pHover, float x, float y, float width, float height) : TexRect(camera, pPressed, x, y, 0, width, height, true)
{
	this->window = window;
	this->hitbox = new AABB(x, y, width, height);
	unpressed = new Texture(pUnpressed);
	pressed = new Texture(pPressed);
	unpressed = new Texture(pUnpressed);
	hover = new Texture(pHover);
}

void Button::update()
{
	if (hitbox->contains(window->getMouseUX(camera), window->getMouseUY(camera)))
	{
		if (window->getMouseLeft())
			state = PRESSED;
		else
			state = HOVERED;
	}
	else
		state = NEUTRAL;
	switch (state)
	{
	case NEUTRAL:
		setTexture(unpressed);
		break;
	case PRESSED:
		setTexture(pressed);
		break;
	case RELEASED:
		setTexture(unpressed);
		break;
	case HOVERED:
		setTexture(hover);
		break;
	default:
		setTexture(unpressed);
		break;
	}
}

AABB* Button::getHitbox()
{
	return hitbox;
}

int Button::getState()
{
	return state;
}

TexButton::TexButton(Window* window, Camera* camera, const char* texture, float x, float y, float width, float height, int id) : Button(window, camera, "res/textures/button_pressed.png", "res/textures/button_unpressed.png", "res/textures/button_hover.png", x, y, width, height)
{
	this->texture = new TexRect(camera, texture, x + (width / 6), y + (height / 6), 0, width - (width / 3), height - (height / 3), true);
	this->id = id;
}

void TexButton::renderTexture()
{
	texture->render();
}

int TexButton::getID()
{
	return id;
}