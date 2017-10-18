#include <SOIL.h>

#include "Texture.h"

Texture::Texture(const char* path)
{
	glGenTextures(1, &tex);
	bind();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glGenerateMipmap(GL_TEXTURE_2D);

	unbind();
}

Texture::~Texture()
{
	glDeleteTextures(1, &tex);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, tex);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}