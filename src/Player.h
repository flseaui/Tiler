#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "Window.h"

#include "Rect.h"

#include "AABB.h"

class Player : public TexRect
{
public:
	Player(Window * window, Camera * camera);
	void update();
	AABB * getHitbox();
	glm::vec3 getVelocity();
	void alignHitbox();
	void hitTop();
	void hitLeft();
	void hitRight();
	void hitBottom();
	void setGravity(float gravity);
	~Player();
private:
	const uint8 SPEED = 84,
		SPACE_HELD = 12,
		WALL_SLIDE = 25;
	Window * window;
	AABB * hitbox;
	bool grounded = true, jump = false;
	uint16 space = 0;
	float gravity;
	glm::vec3 velocity;
};

#endif