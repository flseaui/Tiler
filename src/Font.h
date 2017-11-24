#ifndef __FONT_H_
#define __FONT_H_

#include "Shader.h"
#include "Vao.h"

class Font
{
public:
	Font(const char* font);
private:
	Shader2f * shader;
	static Vao * vao;
	void initVao();
	float r, g, b, a;
	bool independent;
};

#endif