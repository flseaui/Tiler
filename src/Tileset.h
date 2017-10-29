#ifndef __TILESET_H_
#define __TILESET_H_

#include "Tile.h"
#include "Camera.h"

#include <vector>

class Tileset
{
public:
	Tileset(Camera* camera, int size);
	void create();
	Tile* getTile(int index);
private:
	Camera* camera;
	std::vector<Tile*> tiles;
};

#endif