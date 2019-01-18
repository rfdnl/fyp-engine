#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>
#include <memory>
#include <sstream>
#include <iostream>

#include "../../Helper/IncludeGL.hpp"
#include <stb_image/stb_image.h>

class Texture {
private:
	std::string filepath;
	unsigned int id; //, width, height, bpp;
	int width, height, bpp;

public:
	void Init(const std::string& path);
	void Close();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline unsigned int Width() const { return width; }
	inline unsigned int Height() const { return height; }
};

#endif // TEXTURE_HPP
