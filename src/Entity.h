#ifndef __ENTITY_H_
#define __ENTITY_H_

#include <glm/glm.hpp>
#include "AABB.h"

class Entity
{
public:
	Entity();
	glm::vec2 pos, velocity;
	AABB* hitbox;
	float gravity, terminalV;
	bool onGround;
	void update(double deltaTime);
};

#endif