#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "../../Helper/IncludeGL.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray
{
private:
	unsigned int buffer;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl);
	void Bind() const;
	void Unbind() const;
};

/*
	USAGE
	https://www.youtube.com/watch?v=oD1dvfbyf6A&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=14

	float positions[] = {
		-0.5, -0.5f,	// 0
		0.5, -0.5,		// 1
		0.5, 0.5,		// 2
		-0.5, 0.5		// 3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va;
	VertexBuffer vb(positions, 4 * 2 * sizeof(float);
	VertexBufferLayout vbl;

	layout.Push<float>(2);
	va.AddBuffer(vb, vbl);

*/

#endif // VERTEX_ARRAY_HPP
