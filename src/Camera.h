#ifndef __CAMERA_H_
#define __CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(int width, int height);
	~Camera();
	void setDims(int width, int height);
	int getWidth();
	int getHeight();
	void translate(glm::vec3);
	glm::vec3 getPos();
	void setPos(glm::vec3);
	float getRotation();
	void rotate(float angle);
	void setRotation(float angle);
	glm::mat4 getProjection();
	glm::mat4 getView();
	void zoomi();
	void zoomo();
private:
	float width, height, rotation, scale;
	glm::mat4 projection;
	glm::vec3 position;
};

#endif 
