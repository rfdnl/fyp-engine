#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP
#include "../../Helper/IncludeGL.hpp"

class VertexBuffer{
private:
	unsigned int buffer;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

#endif // VERTEX_BUFFER_HPP
