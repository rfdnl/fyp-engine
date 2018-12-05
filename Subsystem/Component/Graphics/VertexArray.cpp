#include "VertexArray.hpp"

VertexArray::VertexArray(){
	std::cout << "VertexArray()" << std::endl;
	glCall(glGenVertexArrays(1, &buffer));
}

VertexArray::~VertexArray(){
	std::cout << "~VertexArray()" << std::endl;
	glCall(glDeleteVertexArrays(1, &buffer));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl){
	Bind();
	vb.Bind();
	const std::vector<VertexBufferElement> elements = vbl.GetElements();
	unsigned int offset = 0;
	for(unsigned int i = 0; i < elements.size(); i++){
			const VertexBufferElement element = elements[i];
		glCall(glEnableVertexAttribArray(i));
		glCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, vbl.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	glCall(glBindVertexArray(buffer));
}

void VertexArray::Unbind() const{
	glCall(glBindVertexArray(0));
}
