#include <GL/glew.h>

#include "Line.h"

Vao * ColLine::vao = 0;

Line::Line(Camera * camera, float x, float y, float z, float xOffset, float yOffset, float zOffset) {
	this->camera = camera;
	position = glm::vec3(x, y, z);
	offset = glm::vec3(xOffset, yOffset, zOffset);
	rotation = 0;
}

glm::mat4 Line::fullTransform()
{
	glm::mat4 temp;
	temp = glm::translate(temp, position);
	temp = glm::rotate<float>(temp, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	return temp;
}


float Line::getX() {
	return position.x;
}

float Line::getY() {
	return position.y;
}

glm::vec3 Line::getPosition() {
	return position;
}

float Line::getRotation() {
	return rotation;
}

void Line::setX(float x) {
	position.x = x;
}

void Line::setY(float y) {
	position.y = y;
}

void Line::setZ(float z) {
	position.z = z;
}

void Line::setPosition(float x, float y) {
	position = glm::vec3(x, y, position.z);
}

void Line::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Line::setOffset(glm::vec3 offset)
{
	this->offset = offset;
}

glm::vec3 Line::getOffset()
{
	return offset;
}

void Line::setPosition(glm::vec3 vector) {
	position = vector;
}

void Line::translateX(float x) {
	position.x += x;
}

void Line::translateY(float y) {
	position.y += y;
}

void Line::translateZ(float z) {
	position.z += z;
}

void Line::translate(float x, float y, float z) {
	position += glm::vec3(x, y, z);
}

void Line::translate(glm::vec3 vector) {
	position += vector;
}

void Line::setRotation(float angle) {
	rotation = angle;
}

void Line::rotate(float angle) {
	rotation += angle;
}

Line::~Line() {}

//Colored Line

ColLine::ColLine(Camera * camera, float r, float g, float b, float a, float x, float y, float z, float xOffset, float yOffset, float zOffset) : Line(camera, x, y, z, xOffset, yOffset, zOffset) {
	shader = Shader::SHADER2C;
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	if (!vao)
		initVao();
}

void ColLine::initVao() {
	float vertices[] = {
		position.x, position.y,
		position.x + offset.x, position.y + offset.y
	};
	unsigned int indices[] = {
		0, 1,
	};
	vao = new Vao(vertices, 2, indices, 2);
}

void ColLine::render() {
	shader->enable();
	shader->setProjection(camera->getProjection());
	shader->setView(camera->getView());
	shader->setModel(fullTransform());
	shader->setColor(r, g, b, a);
	vao->render(1);
	shader->disable();
}

ColLine::~ColLine() {}