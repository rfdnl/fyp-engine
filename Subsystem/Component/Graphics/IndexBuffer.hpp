#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

#include "../../Helper/IncludeGL.hpp"

class IndexBuffer
{
private:
	unsigned int buffer;
	unsigned int count;
public:
	void Init(const unsigned int* data, unsigned int count);
	void Close();
	void Bind() const;
	void Unbind() const;
	inline unsigned int GetCount() const { return count; }
};

#endif // INDEX_BUFFER_HPP
