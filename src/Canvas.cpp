#include "Canvas.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

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

void Canvas::exportCanvas()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "Map Files\0*.sbm\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Save your Map";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	if (GetSaveFileNameA(&ofn))
	{
		std::cout << "You chose the file \"" << filename << "\"\n";
	}
	else
	{
		// All this stuff below is to tell you exactly how you messed up above. 
		// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default: std::cout << "You cancelled.\n";
		}
	}

	//write canvas to map file
	//open selected file in write mode
	std::ofstream outfile;
	outfile.open(filename, std::ios::out | std::ios::trunc);

	for (Layer* layer : layers)
	{
		if (layer != nullptr)
		{
			for (size_t i = 0; i < layer->getWidth(); i++)
			{
				for (size_t j = 0; j < layer->getHeight(); j++)
				{
					outfile << layer->getTile(i, j);
				}
				outfile << std::endl;
			}
			outfile << std::endl;
		}
		outfile.close();
	}
}

void Canvas::importCanvas()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "Map Files\0*.sbm\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a Map";
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	if (GetOpenFileNameA(&ofn))
	{
		std::cout << "You chose the file \"" << filename << "\"\n";
	}
	else
	{
		// All this stuff below is to tell you exactly how you messed up above. 
		// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default: std::cout << "You cancelled.\n";
		}
	}
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