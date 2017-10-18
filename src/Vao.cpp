#include "Vao.h"

Vao::Vao(float vertices[], int32 num, uint32 indices[], int32 count) {
	attrib = 0;
	this->count = count;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	addAttrib(vertices, num, 3);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(int), indices, GL_STATIC_DRAW);
}

void Vao::addAttrib(float data[], int32 length, int32 size) {
	glBindVertexArray(vao);
	glGenBuffers(1, vbos + attrib);
	glBindBuffer(GL_ARRAY_BUFFER, *(vbos + attrib));
	glBufferData(GL_ARRAY_BUFFER, length * size * sizeof(float), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attrib, size, GL_FLOAT, 0, 0, (void*)0);
	++attrib;
}

void Vao::render() {
	glBindVertexArray(vao);
	for (int i = 0; i < attrib; ++i)
		glEnableVertexAttribArray(i);
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)0);
	for (int i = 0; i < attrib; ++i)
		glDisableVertexAttribArray(i);
}

Vao::~Vao() {
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(attrib, vbos);
	glDeleteVertexArrays(1, &vao);
}