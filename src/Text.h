#ifndef __TEXT_H_
#define __TEXT_H_

#include "Shader.h"
#include "Vao.h"

class Text
{
public:
	Text(const char* text);
	void update();
	void render();
	void setContent(const char* content);
	const char* getContent();
private:
	const char* content;
	Shader2f * shader;
	static Vao * vao;
	void initVao();
	float r, g, b, a;
	bool independent;
};

#endif