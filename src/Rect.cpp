#include <GL/glew.h>

#include "Rect.h"

Vao * ColRect::vao = 0;
Vao * TexRect::vao = 0;

Rect::Rect(Camera * camera, float x, float y, float z, float width, float height) {
	this->camera = camera;
	this->width = width;
	this->height = height;
	position = glm::vec3(x, y, z);
	rotation = 0;
}

glm::mat4 Rect::fullTransform()
{
	glm::mat4 temp;
	temp = glm::translate(temp, position);
	temp = glm::rotate<float>(temp, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	temp = glm::scale(temp, glm::vec3(width, height, 1));
	return temp;
}


float Rect::getX() {
	return position.x;
}

float Rect::getY() {
	return position.y;
}

glm::vec3 Rect::getPosition() {
	return position;
}

float Rect::getRotation() {
	return rotation;
}

float Rect::getWidth() {
	return width;
}

float Rect::getHeight() {
	return height;
}

glm::vec3 Rect::getDims() {
	return glm::vec3(width, height, 0);
}

void Rect::setX(float x) {
	position.x = x;
}

void Rect::setY(float y) {
	position.y = y;
}

void Rect::setZ(float z) {
	position.z = z;
}

void Rect::setPosition(float x, float y) {
	position = glm::vec3(x, y, position.z);
}

void Rect::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Rect::setPosition(glm::vec3 vector) {
	position = vector;
}

void Rect::translateX(float x) {
	position.x += x;
}

void Rect::translateY(float y) {
	position.y += y;
}

void Rect::translateZ(float z) {
	position.z += z;
}

void Rect::translate(float x, float y, float z) {
	position += glm::vec3(x, y, z);
}

void Rect::translate(glm::vec3 vector) {
	position += vector;
}

void Rect::setRotation(float angle) {
	rotation = angle;
}

void Rect::rotate(float angle) {
	rotation += angle;
}

void Rect::scale(float scale) {
	width *= scale;
	height *= scale;
}

void Rect::scale(float x, float y) {
	width *= x;
	height *= y;
}

void Rect::setWidth(float width) {
	this->width = width;
}

void Rect::setHeight(float height) {
	this->height = height;
}

void Rect::setDims(float width, float height) {
	this->width = width;
	this->height = height;
}

Rect::~Rect() {}

//ColRect - Colored Rectangle

ColRect::ColRect(Camera * camera, float r, float g, float b, float a, float x, float y, float z, float width, float height) : Rect(camera, x, y, z, width, height) {
	shader = Shader::SHADER2C;
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	if (!vao)
		initVao();
}

void ColRect::initVao() {
	float vertices[] = {
		1, 0, 0,
		1, 1, 0,
		0, 1, 0,
		0, 0, 0
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	vao = new Vao(vertices, 4, indices, 6);
}

void ColRect::render() {
	shader->enable();
	shader->setProjection(camera->getProjection());
	shader->setView(camera->getView());
	shader->setModel(fullTransform());
	shader->setColor(r, g, b, a);
	vao->render();
	shader->disable();
}

ColRect::~ColRect() {}

//TexRect - Textured Rectangle

TexRect::TexRect(Camera * camera, const char path[], float x, float y, float z, float width, float height) : Rect(camera, x, y, z, width, height) {
	texture = new Texture(path);
	shader = Shader::SHADER2T;
	if (!vao)
		initVao();
}

void TexRect::render() {
	texture->bind();
	shader->enable();
	shader->setProjection(camera->getProjection());
	shader->setView(camera->getView());
	shader->setModel(fullTransform());
	vao->render();
	shader->disable();
	texture->unbind();
}

void TexRect::initVao() {
	float vertices[] = {
		1, 0, 0,
		1, 1, 0,
		0, 1, 0,
		0, 0, 0
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	float texCoords[] = {
		1, 0,
		1, 1,
		0, 1,
		0, 0
	};
	vao = new Vao(vertices, 4, indices, 6);
	vao->addAttrib(texCoords, 4, 2);
}

TexRect::~TexRect() {
	delete texture;
}