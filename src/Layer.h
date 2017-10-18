#ifndef __LAYER_H_
#define __LAYER_H_

#include "Tile.h"
#include <vector>

class Layer
{
public:
	Layer(const char* title, int width, int height, int tileWidth, int tileHeight);
	~Layer();
	void render();
	void update();
	bool enabled();
	void setEnabled(bool state);
	const char* getTitle();
	void setTitle(const char* title);
	Tile* getTile(int xIndex, int yIndex);
	void setTile(int xIndex, int yIndex, Tile* tile);
	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);
private:
	int height;
	int width;
	int tileWidth;
	int tileHeight;
	std::vector<Tile*> tiles;
	bool disabled;
	const char* title;
};

#endif