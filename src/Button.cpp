#include "Button.h"

Button::Button(Window* window, Camera* camera, const char* pPressed, const char* pUnpressed, const char* pHover, float x, float y, float width, float height) : TexRect(camera, pPressed, x, y, 0, width, height)
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
	if (hitbox->contains(window->getMouseCX(camera), window->getMouseCY(camera)))
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