#ifndef __VAO_H_
#define __VAO_H_

#include "Types.h"

#include <GL/glew.h>

class Vao 
{
	public:
		Vao(float verts[], int32 num, uint32 indices[], int32 count);
		void addAttrib(float data[], int32 num, int32 stride);
		void render();
		~Vao();
	private:
		uint32 vao, ibo, vbos[15], count;
		uint8 attrib;
};

#endif