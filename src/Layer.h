#ifndef __LAYER_H_
#define __LAYER_H_

#include "Tile.h"
#include "Tileset.h"
#include <vector>

class Layer
{
public:
	Layer(const char* title, int width, int height, Tileset* tileset, int tileWidth, int tileHeight);
	~Layer();
	void render();
	void update();
	bool enabled();
	void setEnabled(bool state);
	const char* getTitle();
	void setTitle(const char* title);
	int getTile(int xIndex, int yIndex);
	void setTile(int xIndex, int yIndex, int tile);
	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);
	Tileset* getTileset();
private:
	int height;
	int width;
	int tileWidth;
	int tileHeight;
	std::vector<int> map;
	Tileset* tileset;
	bool disabled;
	const char* title;
};

#endif