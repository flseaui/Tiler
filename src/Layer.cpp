#include "Layer.h"
#include <iostream>
#include <queue>


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
	std::fill(map.begin(), map.end(), 0);
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
	if (!(xIndex >= width || xIndex < 0 || yIndex >= height || yIndex < 0))
		map.at(xIndex * height + yIndex) = tile;
}

/*void Layer::fill(int xIndex, int yIndex, int tile)
{
	if (!(xIndex >= width || xIndex <= 0 || yIndex >= height || yIndex <= 0))
	{
		bool* checked = new bool[width * height];
		int target = getTile(xIndex, yIndex);
		for (int i = -1; i < 1; i++)
			for (int j = -1; j < 1; j++)
			{
				if (map.at((xIndex + i) * height + (yIndex + j)) == target)
				{
					map.at((xIndex + i) * height + (yIndex + j)) = tile;
					if (checked[(xIndex + i) * height + (yIndex + j)] == false)
						fill(xIndex + i, yIndex + j, tile);
					else
						checked[(xIndex + i) * height + (yIndex + j)] = true;
				}
			}
		delete checked;
	}
}*/

/*void Layer::fill(int x, int y, int tile)
{
		bool* checked = new bool[width * height];

		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				fillCheck(x + i, y + j, tile);
			}

		delete checked;
}*/

void Layer::fill(int x, int y, int tile)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		int target = getTile(x, y);
		if (target == tile) return;

		struct node { int x; int y; };
		std::queue<node> nodes;

		map.at(x * height + y) = tile;
		nodes.push({ x, y });

		while (nodes.size() > 0)
		{
			auto n = nodes.front();
			nodes.pop();
			map.at(n.x * height + n.y) = tile;
			std::queue<node> subNodes;
			for (int i = n.x - 1; map.at(((i > 0 ? i : 0) * height) + n.y) == target && i >= 0; --i)
			{
				subNodes.push({ i, n.y });
				subNodes.push({ i + 1, n.y });
			}
				for (int j = n.x + 1; map.at(((j < width - 1 ? j : width - 1) * height) + n.y) == target && j < width; ++j)
				{
					subNodes.push({ j, n.y });
					subNodes.push({ j - 1, n.y });
				}
			do
			{
				if (subNodes.size() == 0)
				{
					if (map.at(n.x * height + (n.y > 0 ? n.y - 1 : 0)) == target)
						nodes.push({ n.x, n.y - 1 });
					if (map.at(n.x * height + (n.y < height - 1 ? n.y + 1 : height - 1)) == target)
						nodes.push({ n.x, n.y + 1 });
				}
				else
				{
					auto sn = subNodes.front();
					subNodes.pop();
					map.at(sn.x * height + sn.y) = tile;
					if (map.at(sn.x * height + (sn.y > 0 ? sn.y - 1 : 0)) == target)
						nodes.push({ sn.x, sn.y - 1 });
					if (map.at(sn.x * height + (sn.y < height - 1 ? sn.y + 1 : height - 1)) == target)
						nodes.push({ sn.x, sn.y + 1 });
				}
			}
			while (subNodes.size() > 0);
		}
	}
}


void Layer::fillCheck(int x, int y, int tile)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		int target = getTile(x, y);
		if (target == tile) return;
		if (map.at(x * height + y) == target)
			map.at(x * height + y) = tile;
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