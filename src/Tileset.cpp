#include <stdio.h>
#include <fstream>

#include "Tileset.h"

Tileset::Tileset(Camera* camera, int size)
{
	this->camera = camera;
	tiles.resize(size);
	create();
}

void Tileset::create()
{
	tiles.at(0) = new Tile(camera, "res/textures/sky_tile.png", false, 0, 32, 32);
	tiles.at(1) = new Tile(camera, "res/textures/stone_tile.png", true, 0, 32, 32);
	tiles.at(2) = new Tile(camera, "res/textures/cmbt.png", true, 0, 32, 32);
	tiles.at(3) = new Tile(camera, "res/textures/clab.png", true, 0, 32, 32);
}

Tile* Tileset::getTile(int index)
{
	return tiles.at(index);
}