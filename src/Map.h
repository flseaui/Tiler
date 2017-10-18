#ifndef MAP
#define MAP

#include "Types.h"

#include "Window.h"
#include "Camera.h"

#include "Player.h"
#include "Tile.h"

class Map {
	public:
		Map(Window * window, Camera * camera, uint16 width, uint16 height);
		void update();
		bool checkCollision();
		void render();
		~Map();
	private:
		const static uint16 NUM_TILES = 2;
		const uint8 DIMS = 16;
		Camera * camera;
		Player * player;
		Tile * tiles[NUM_TILES];
		uint16 * map, width, height;
};

#endif