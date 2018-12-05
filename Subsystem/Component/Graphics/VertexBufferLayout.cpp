#include "VertexBufferLayout.hpp"

template<typename T>
void Push(unsigned int count)
{
	//static_assert(false, "this function has to be implemented for desired type");
	ASSERT(false);
}

template<> void VertexBufferLayout::Push<float>(unsigned int count){
	elements.push_back({GL_FLOAT, count, GL_FALSE});
	//stride += sizeof(GLfloat);
	stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<> void VertexBufferLayout::Push<unsigned int>(unsigned int count){
	elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
	//stride += sizeof(GLuint);
	stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<> void VertexBufferLayout::Push<unsigned char>(unsigned int count){
	elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
	//stride += sizeof(GLubyte);
	stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
