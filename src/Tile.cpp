#include "Tile.h"

Tile::Tile(Camera * camera, const char* path, bool solid, float z, float width, float height) : TexRect(camera, path, 0, 0, 0, width, height) {
	this->solid = solid;
	hitbox = new AABB(0, 0, width, height);
}

bool Tile::isSolid() {
	return solid;
}

void Tile::setSolid(bool solid) {
	this->solid = solid;
}

AABB* Tile::getHitbox()
{
	return hitbox;
}

Tile::~Tile() {}