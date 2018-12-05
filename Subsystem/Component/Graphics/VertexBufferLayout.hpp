#ifndef VERTEX_BUFFER_LAYOUT_HPP
#define VERTEX_BUFFER_LAYOUT_HPP
#include <vector>
#include "../../Helper/IncludeGL.hpp"

struct VertexBufferElement{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type){
		switch(type){
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout{
private:
	unsigned int stride;
	std::vector<VertexBufferElement> elements;
public:
	VertexBufferLayout():stride(0){
		std::cout << "VertexBufferLayout()" << std::endl;
	}
	~VertexBufferLayout(){
		std::cout << "~VertexBufferLayout()" << std::endl;
	}

	template<typename T>
	void Push(unsigned int count);

	inline const std::vector<VertexBufferElement> GetElements() const { return elements; }
	inline unsigned int GetStride() const { return stride; }
};



#endif // VERTEX_BUFFER_LAYOUT_HPP
