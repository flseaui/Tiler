#ifndef __CANVAS_H_
#define __CANVAS_H_

class Canvas
{
public:
	int getWidth();
	int getHeight();
	int getTileWidth();
	int getTileHeight();
private:
	int width, height, tileWidth, tileHeight;
	Canvas();
};

#endif