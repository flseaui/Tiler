#ifndef TILE
#define TILE

#include "Camera.h"

#include "Rect.h"

class Tile : public TexRect {
	public:
		Tile(Camera * camera, const char* path, bool solid, float z, float width, float height);
		bool isSolid();
		void setSolid(bool solid);
		~Tile();
	private:
		bool solid;
};

#endif