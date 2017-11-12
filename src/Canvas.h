#ifndef __CANVAS_H_
#define __CANVAS_H_

#include "Layer.h"

#include <vector>

#include "AABB.h"
#include "Window.h"
#include "Rect.h"
#include "Tileset.h"

class Canvas
{
public:
	Canvas(Window* window, Camera* camera, int width, int height, int tileWidth, int tileHeight);
	~Canvas();
	void render();
	void update(int curTile);
	int getWidth();
	int getHeight();
	int getTileWidth();
	int getTileHeight();
	void addLayer();
	void removeLayer();
	std::vector <Layer*> getLayers();
	void setLayers(std::vector <Layer*> layer);
	Layer* getLayer(int index);
	void setLayer(int index, int otherIndex);
	void setLayer(int index, Layer* layer);
	Layer* getCurrentLayer();
	void setCurrentLayer(Layer* layer);
	int getCurrentLayerID();
	void setCurrentLayerByID(int id, int index);
	void setCurrentLayerByID(int id, Layer* layer);
	void setBucket(bool state);
private:
	Window* window;
	Camera* camera;
	int width, height, tileWidth, tileHeight;
	std::vector <Layer*> layers;
	Tileset* tileset;
	AABB* hitbox;
	ColRect* line;
	Tile* tex, *hTex;
	bool bucket;
};

#endif