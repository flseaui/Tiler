#include <iostream>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>

#include "AABB.h"

#include "Map.h"

Map::Map(Window * window, Camera * camera, uint16 width, uint16 height) {
	this->camera = camera;
	this->width = width;
	this->height = height;
	map = new uint16[width * height];
	tiles[0] = new Tile(camera, "res/textures/sky_tile.png", false, 0.5, DIMS, DIMS);
	tiles[1] = new Tile(camera, "res/textures/stone_tile.png", true, 0.5, DIMS, DIMS);
	for (uint16 i = 0; i < width; i++)
		for (uint16 j = 0; j < height; j++)
		{
			if (j == height-1 || j == 0 || i == 0 || i == width - 1)
				map[i * height + j] = 1;
			else
				map[i * height + j] = 0;
		}
	player = new Player(window, camera);
}

void Map::update() {
	player->update();
	//camera->setPos(glm::vec3(player->getX(), player->getY(), 0));
	while (checkCollision());
//	std::cout << player->getHitbox()->getPosition().x << ", " << player->getHitbox()->getPosition().y << std::endl;
}

bool Map::checkCollision() {
	AABB * playerHit = player->getHitbox();
	AABB * closest = 0;
	AABB * current = 0;
	glm::vec3 closestLength;
	int minX = floor(player->getX() / DIMS);
	int maxX = ceil(player->getX() / DIMS);
	int minY = floor(player->getY() / DIMS);
	int maxY = ceil(player->getY() / DIMS);
	if (minX >= 0 && maxX < width && minY >= 0 && maxY < height) {
		for (uint8 i = minX; i <= maxX; ++i) {
			for (uint8 j = minY; j <= maxY; ++j) {
				Tile * curTile = tiles[map[i * height + j]];
				if (curTile->isSolid()) {
					if (!closest) {
						closest = new AABB(i * DIMS, j * DIMS, DIMS, DIMS);
						closestLength = closest->getCenter() + (-playerHit->getCenter());
					}
					else {
						if (current)
							delete current;
						current = new AABB(i * DIMS, j * DIMS, DIMS, DIMS);
						glm::vec3 curLength = current->getCenter() + (-playerHit->getCenter());
						if (glm::length2(curLength) < glm::length2(closestLength)) {
							closestLength = curLength;
							delete closest;
							closest = current;
							current = 0;
						}
					}
				}
			}
		}
	}
	bool ret = false;
	if (closest) {
		if (closest->collides(playerHit)) {
			glm::vec3 transform = closest->getTransform(playerHit);
			if ((player->getVelocity().y < 0 && transform.y < 0) || (player->getVelocity().y > 0 && transform.y > 0)) {
				transform.x = closest->getTransformX(playerHit);
				transform.y = 0;
			}
			else if ((player->getVelocity().x < 0 && transform.x < 0) || (player->getVelocity().x > 0 && transform.x > 0)) {
				transform.y = closest->getTransformY(playerHit);
				transform.x = 0;
			}
			player->translate(transform);
			player->alignHitbox();
			if (transform.y < 0)
				player->hitBottom();
			else if (transform.x > 0)
				player->hitLeft();
			else if (transform.x < 0)
				player->hitRight();
			else
				player->hitTop();
			ret = true;
		}
		if (current)
			delete current;
		delete closest;
	}
	return ret;
}

void Map::render() {
	player->render();
	/*int minX = fmax(camera->getPos().x / DIMS, 0);
	int maxX = fmin((camera->getPos().x + camera->getWidth()) / DIMS, width);
	int minY = fmax(camera->getPos().y / DIMS, 0);
	int maxY = fmin((camera->getPos().y + camera->getHeight()) / DIMS, height);*/
	for (uint16 i = 0; i < width; ++i) {
		for (uint16 j = 0; j < height; ++j) {
			tiles[map[i * height + j]]->setPosition(i * DIMS, j * DIMS);
			tiles[map[i * height + j]]->render();
		}
	}
}

Map::~Map() {
	delete [] map;
	for (uint16 i = 0; i < NUM_TILES; ++i)
		delete tiles[i];
}