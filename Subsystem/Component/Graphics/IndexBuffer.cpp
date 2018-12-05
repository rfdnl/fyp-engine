#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):count(count)
{
	std::cout << "IndexBuffer()" << std::endl;
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	glCall(glGenBuffers(1, &buffer));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer(){
	std::cout << "~IndexBuffer()" << std::endl;
	glCall(glDeleteBuffers(1, &buffer));
}

void IndexBuffer::Bind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer));
}

void IndexBuffer::Unbind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
