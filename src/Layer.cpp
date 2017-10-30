#include "Layer.h"
#include <iostream>

Layer::Layer(const char* title, int width, int height, Tileset* tileset, int tileWidth, int tileHeight)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->tileset = tileset;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	disabled = false;
	map.resize(width * height);
}

void Layer::render()
{
	for (uint16 i = 0; i < width; ++i)
		for (uint16 j = 0; j < height; ++j)
		{
			if (map[i * height + j] != NULL)
			{
				tileset->getTile(map[i * height + j])->setPosition(i * tileWidth, j * tileHeight);
				tileset->getTile(map[i * height + j])->render();
			}
		}
}

void Layer::update()
{

}

bool Layer::enabled()
{
	return !disabled;
}

void Layer::setEnabled(bool state)
{
	disabled = !state;
}

const char* Layer::getTitle()
{
	return title;
}

void Layer::setTitle(const char* title)
{
	this->title = title;
}

int Layer::getTile(int xIndex, int yIndex)
{
	return map.at(xIndex * height + yIndex);
}

void Layer::setTile(int xIndex, int yIndex, int tile)
{
	std::cout << "kkk" << std::endl;
	if (!(xIndex >= width || xIndex < 0 || yIndex >= height || yIndex < 0))
		map.at(xIndex * height + yIndex) = tile;
}

void Layer::fill(int xIndex, int yIndex, int tile)
{
	if (!(xIndex >= width || xIndex < 0 || yIndex >= height || yIndex < 0))
	{
		int target = getTile(xIndex, yIndex);
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (map.at(xIndex > 0 ? xIndex + i : 0 * height + yIndex > 0 ? yIndex + j : 0) == target)
				{
					map.at(xIndex > 0 ? xIndex + i : 0 * height + yIndex > 0 ? yIndex + j : 0) = tile;
				}
			}
	}
}

int Layer::getWidth()
{
	return width;
}

int Layer::getHeight()
{
	return height;
}

void Layer::setWidth(int width)
{
	this->width = width;
}

void Layer::setHeight(int height)
{
	this->height = height;
}

Tileset* Layer::getTileset()
{
	return tileset;
}

Layer::~Layer()
{

}