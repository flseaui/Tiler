#include "Canvas.h"
#include <iostream>

Canvas::Canvas(Window* window, Camera* camera, int width, int height, int tileWidth, int tileHeight)
{
	this->window = window;
	this->camera = camera;
	this->width = width;
	this->height = height;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	line = new ColRect(camera, 1, 1, 1, 1, 0, 0, 0, .1f, 100, false);
	hitbox = new AABB(0, 0, width * tileWidth, height * tileHeight);
	tileset = new Tileset(camera, 6);
	layers.resize(width * height);
	setLayer(0, new Layer("base layer", width, height, tileset, tileWidth, tileHeight));
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			getCurrentLayer()->setTile(i, j, 0);
	camera->setPos(glm::vec3(-(width * tileWidth) / 2, -((height * tileHeight) / 9), 0));

	bucket = false;
}

void Canvas::update(int curTile)
{
	getCurrentLayer()->update();
	/*for (int i = 0; i < getCurrentLayer()->getWidth(); i++)
		for (int j = 0; j < getCurrentLayer()->getHeight(); j++)
		{
			if (window->getMouseLeft())
			{
				std::cout << "big ol kek" << std::endl;
				if (getCurrentLayer()->getTile(i, j) != nullptr)
				{
					std::cout << "big ol" << std::endl;
					if (hitbox->contains(window->getMouseCX(camera), window->getMouseCY(camera)))
					{
						std::cout << "x: " << i << " y: " << j << std::endl;
						getCurrentLayer()->setTile(window->getMouseCX(camera) / tileWidth, window->getMouseCY(camera) / tileHeight, tex);
					}
				}
			}
		}*/
	if (window->getMouseLeft())
	{
		if (bucket)
			getCurrentLayer()->fill(window->getMouseCX(camera) / tileWidth, window->getMouseCY(camera) / tileHeight, curTile);
		else
			getCurrentLayer()->setTile(window->getMouseCX(camera) / tileWidth, window->getMouseCY(camera) / tileHeight, curTile);	
	}
}

void Canvas::render()
{
	
	//render grid
	line->setWidth(.1f);
	line->setHeight(width * tileWidth);
	for (int i = 0; i <= width; ++i)
	{
		line->setPosition(i * tileWidth, 0);
		line->render(true);
	}

	line->setWidth(height * tileHeight);
	line->setHeight(.1f);
	for (int i = 0; i <= height; ++i)
	{
		line->setPosition(0, i * tileHeight);
		line->render(true);
	}
	//hTex->setPosition(0, 0);
	//hTex->setDims(width * tileWidth, height * tileHeight);
	//hTex->render();
	//render layers
	for (Layer* l : layers)
		if (l != nullptr)
			if (l->enabled())
				l->render();
}

int Canvas::getWidth()
{
	return width;
}

int Canvas::getHeight()
{
	return height;
}

int Canvas::getTileWidth()
{
	return tileWidth;
}

int Canvas::getTileHeight()
{
	return tileHeight;
}

void Canvas::addLayer()
{
	layers.insert(layers.begin(), new Layer("emtpy layer", width, height, tileset, tileWidth, tileHeight));
}

void Canvas::removeLayer()
{  
	layers.erase(layers.begin() + getCurrentLayerID());
}

std::vector <Layer*> Canvas::getLayers()
{
	return layers;
}

void Canvas::setLayers(std::vector <Layer*> layer)
{
	this->layers = layers;
}

Layer* Canvas::getLayer(int index)
{
	return this->layers.at(index);
}

void Canvas::setLayer(int index, int otherIndex)
{
	layers.at(index) = layers.at(otherIndex);
}

void Canvas::setLayer(int index, Layer* layer)
{
	layers.at(index) =  layer;
}

Layer* Canvas::getCurrentLayer()
{
	for (Layer* l : layers)
		if (l->enabled())
			return l;
}

void Canvas::setCurrentLayer(Layer* layer)
{
	for (Layer* l : layers)
		if (l->enabled())
			l = layer;
}

int Canvas::getCurrentLayerID()
{
	for (int i = 0; i < layers.size(); ++i)
		if (layers[i]->enabled())
			return i;
}

void Canvas::setCurrentLayerByID(int id, int index)
{
	for (int i = 0; i < layers.size(); ++i)
		if (i == id)
			layers[i] = layers[index];
}

void Canvas::setCurrentLayerByID(int id, Layer* layer)
{
	for (int i = 0; i < layers.size(); ++i)
		if (i == id)
			layers[i] = layer;
}

void Canvas::setBucket(bool state)
{
	bucket = state;
}

Canvas::~Canvas()
{
	std::vector<Layer*>().swap(layers);
}