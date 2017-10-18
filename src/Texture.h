#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include <GL/glew.h>

class Texture
{
public:
	Texture(const char* path);
	~Texture();
	void bind();
	void unbind();
private:
	GLuint tex;
	int id, width, height;
};

#endif