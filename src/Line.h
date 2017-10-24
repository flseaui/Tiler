#ifndef __LINE_H_
#define __LINE_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Texture.h"
#include "Shader.h"
#include "Vao.h"

class Line {
public:
	virtual void render() = 0;
	glm::mat4 fullTransform();
	float getX();
	float getY();
	glm::vec3 getPosition();
	float getRotation();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setPosition(float x, float y);
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 vector);
	void setOffset(glm::vec3 offset);
	glm::vec3 getOffset();
	void translateX(float x);
	void translateY(float y);
	void translateZ(float z);
	void translate(float x, float y, float z);
	void translate(glm::vec3 vector);
	void setRotation(float angle);
	void rotate(float angle);
	~Line();
protected:
	Camera * camera;
	glm::vec3 position;
	glm::vec3 offset;
	float rotation;
	Line(Camera * camera, float x, float y, float z, float xOffset, float yOffset, float zOffset);
};

class ColLine : public Line {
public:
	ColLine(Camera * camera, float r, float g, float b, float a, float x, float y, float z, float xOffset, float yOffset, float zOffset);
	void render();
	~ColLine();
private:
	Shader2c * shader;
	static Vao * vao;
	void initVao();
	float r, g, b, a;
};


#endif