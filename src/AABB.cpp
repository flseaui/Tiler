#include "AABB.h"

AABB::AABB(float x, float y, float width, float height) {
	center = glm::vec3(x + width / 2, y + height / 2, 0);
	halfExtent = glm::vec3(width / 2, height / 2, 0);
}

bool AABB::collides(AABB * hitbox) {
	return abs(center.x - hitbox->center.x) < abs(halfExtent.x + hitbox->halfExtent.x) &&
		   abs(center.y - hitbox->center.y) < abs(halfExtent.y + hitbox->halfExtent.y);
}

glm::vec3 AABB::getTransform(AABB * hitbox) {
	float dx = abs(center.x - hitbox->center.x) - abs(halfExtent.x + hitbox->halfExtent.x);
	float dy = abs(center.y - hitbox->center.y) - abs(halfExtent.y + hitbox->halfExtent.y);
	(abs(dx) > abs(dy) ? dx : dy) = 0;
	if (dx && center.x < hitbox->center.x) dx = -dx;
	else if (center.y < hitbox->center.y) dy = -dy;
	return glm::vec3(dx, dy, 0);
}

float AABB::getTransformX(AABB * hitbox) {
	float dx = abs(center.x - hitbox->center.x) - abs(halfExtent.x + hitbox->halfExtent.x);
	if (center.x < hitbox->center.x) dx = -dx;
	return dx;
}

float AABB::getTransformY(AABB * hitbox) {
	float dy = abs(center.y - hitbox->center.y) - abs(halfExtent.y + hitbox->halfExtent.y);
	if (center.y < hitbox->center.y) dy = -dy;
	return dy;
}

glm::vec3 AABB::getCenter() {
	return center;
}

void AABB::setPosition(float x, float y) {
	center = glm::vec3(x + halfExtent.x, y + halfExtent.y, 0);
}

void AABB::setPosition(glm::vec3 vector) {
	center = glm::vec3(vector.x + halfExtent.x, vector.y + halfExtent.y, 0);
}

glm::vec3 AABB::getPosition()
{
	return glm::vec3(center.x-halfExtent.x, center.y-halfExtent.y, 0);
}

void AABB::setCenter(glm::vec3 vector) {
	center = glm::vec3(vector);
}

AABB::~AABB() {}