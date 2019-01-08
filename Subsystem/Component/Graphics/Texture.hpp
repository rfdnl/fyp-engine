#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>
#include <memory>
#include <sstream>
#include <iostream>

#include "../../Helper/IncludeGL.hpp"
#include "../../Helper/ILoggable.hpp"
#include "IDrawable.hpp"

class Texture {
private:
	std::string filepath;
	unsigned int id; //, width, height, bpp;
	int width, height, bpp;

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline unsigned int Width() const { return width; }
	inline unsigned int Height() const { return height; }
};

#endif // TEXTURE_HPP
