#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray
{
private:
	unsigned int buffer;
public:
	void Init();
	void Close();
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl);
	void Bind() const;
	void Unbind() const;
};

#endif // VERTEX_ARRAY_HPP
