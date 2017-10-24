#include "Layer.h"

Layer::Layer(const char* title, int width, int height, int tileWidth, int tileHeight)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	disabled = false;
	tiles.resize(width * height);
}

void Layer::render()
{
	for (uint16 i = 0; i < width; ++i)
		for (uint16 j = 0; j < height; ++j)
		{
			if (tiles[i * height + j] != nullptr)
			{
				tiles[i * height + j]->setPosition(i * tileWidth, j * tileHeight);
				tiles[i * height + j]->render();
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

Tile* Layer::getTile(int xIndex, int yIndex)
{
	return tiles.at(xIndex * height + yIndex);
}

void Layer::setTile(int xIndex, int yIndex, Tile* tile)
{
	if (!(xIndex >= width || xIndex < 0 || yIndex >= height || yIndex < 0))
		tiles.at(xIndex * height + yIndex) = tile;
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

Layer::~Layer()
{

}