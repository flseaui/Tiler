#include "Canvas.h"

Canvas::Canvas()
{

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
	layers.insert(layers.begin(), new Layer*());
}

void Canvas::removeLayer()
{
	layers.clear(getCurrentLayerID);
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
	layers.insert(index, layers.at(otherIndex));
}

void Canvas::setLayer(int index, Layer* layer)
{
	layers.insert(index, layer);
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
	delete layers;
}