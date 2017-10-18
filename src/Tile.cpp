#include "Tile.h"

Tile::Tile(Camera * camera, const char* path, bool solid, float z, float width, float height) : TexRect(camera, path, 0, 0, 0, 16, 16) {
	this->solid = solid;
}

bool Tile::isSolid() {
	return solid;
}

void Tile::setSolid(bool solid) {
	this->solid = solid;
}

Tile::~Tile() {}