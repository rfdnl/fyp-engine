#include "VertexBuffer.hpp"

void VertexBuffer::Init(const void* data, unsigned int size){
	std::cout << "VertexBuffer()" << std::endl;
	glCall(glGenBuffers(1, &buffer));
	glCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Close(){
	std::cout << "~VertexBuffer()" << std::endl;
	glCall(glDeleteBuffers(1, &buffer));
}

void VertexBuffer::Bind() const {
	glCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
}

void VertexBuffer::Unbind() const {
	glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
