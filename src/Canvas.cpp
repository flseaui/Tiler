#include "Canvas.h"
#include <iostream>

Canvas::Canvas(Window* window, Camera* camera, int width, int height, int tileWidth, int tileHeight)
{
	this->window = window;
	this->width = width;
	this->height = height;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	line = new ColRect(camera, 1, 1, 1, 1, 0, 0, 0, .1f, 100);
	tex = new Tile(camera, "res/textures/stone_texture.png", false, 0, 32, 32);
	layers.resize(width * height);
	setLayer(0, new Layer("base layer", width, height, tileWidth, tileHeight));
}

void Canvas::update()
{
	getCurrentLayer()->update();
	for (int i = 0; i < getCurrentLayer()->getWidth(); i++)
		for (int i = 0; i < getCurrentLayer()->getHeight(); i++)
		{
			if (window->getMouseLeft())
			{
			//	std::cout << "x: " << window->getMouseX() << " y: " << window->getMouseY() << std::endl;
				if (window->getMouseX() > 0 && window->getMouseX() < width * 50 && window->getMouseY() > 0 && window->getMouseY() < height * 50)
				{
					std::cout << "x: " << window->getMouseX() << " y: " << window->getMouseY() << std::endl;
					getCurrentLayer()->setTile(window->getMouseX() / 50, window->getMouseY() / 50, tex);
				}
			}
		}
}

void Canvas::render()
{
	//render grid
	line->setWidth(.1f);
	line->setHeight(width * 8);
	for (int i = 0; i <= width; ++i)
	{
		line->setPosition(i * 8, 0);
		line->render();
	}

	line->setWidth(height * 8);
	line->setHeight(.1f);
	for (int i = 0; i <= height; ++i)
	{
		line->setPosition(0, i * 8);
		line->render();
	}

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
	layers.insert(layers.begin(), new Layer("emtpy layer", width, height, tileWidth, tileHeight));
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
	layers.insert(layers.begin() + index, layers.at(otherIndex));
}

void Canvas::setLayer(int index, Layer* layer)
{
	layers.insert(layers.begin() + index, layer);
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

Canvas::~Canvas()
{
	std::vector<Layer*>().swap(layers);
}