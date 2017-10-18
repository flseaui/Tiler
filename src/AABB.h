#ifndef __AABB_H_
#define __AABB_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class AABB {
public:
	AABB(float x, float y, float width, float height);
	bool collides(AABB * hitbox);
	glm::vec3 getTransform(AABB * hitbox);
	float getTransformX(AABB * hitbox);
	float getTransformY(AABB * hitbox);
	glm::vec3 getCenter();
	void setPosition(float x, float y);
	void setPosition(glm::vec3 vector);
	glm::vec3 getPosition();
	void setCenter(glm::vec3 vector);
	~AABB();
private:
	glm::vec3 center;
	glm::vec3 halfExtent;
};

#endif