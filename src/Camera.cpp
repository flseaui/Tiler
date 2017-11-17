#include <iostream>

#include "Camera.h"

Camera::Camera(int width, int height)
{
	rotation = 0;
	setDims(width, height);
	setPos(glm::vec3(0, 0, 0));
	scale = 1;
}

Camera::~Camera()
{

}

void Camera::setDims(int width, int height)
{
	this->width = width;
	this->height = height;
	projection = glm::ortho(0.0f, (float) width, (float) height, 0.0f, -10.0f, 10.0f);
}

int Camera::getWidth()
{
	return width;
}

int Camera::getHeight()
{
	return height;
}

float Camera::getScale()
{
	return scale;
}

void Camera::translate(glm::vec3 vec)
{
	position.x -= vec.x;
	position.y -= vec.y;
	position.z -= vec.z;
}

void Camera::zoomi()
{
	scale+=0.1f;
}

void Camera::zoomo()
{
	scale-=0.1;
}

glm::vec3 Camera::getPos()
{
	return position;
}

void Camera::setPos(glm::vec3 vec)
{
	position.x = -vec.x;
	position.y = -vec.y;
	position.z = -vec.z;
}

float Camera::getRotation()
{
	return -rotation;
}

void Camera::rotate(float angle)
{
	rotation -= angle;
}

void Camera::setRotation(float angle)
{
	rotation = -angle;
}

glm::mat4 Camera::getProjection()
{
	return projection;
}

glm::mat4 Camera::getView()
{
	glm::mat4 temp;
	temp = glm::translate(temp, position);
	temp = glm::translate(temp, glm::vec3(-(width*scale / 2), -(height*scale / 2), 0));
	temp = glm::rotate(temp, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	temp = glm::scale(temp, glm::vec3(scale, scale, 1));
	temp = glm::translate(temp, glm::vec3((width / 2), (height / 2), 0));
	return temp;
}