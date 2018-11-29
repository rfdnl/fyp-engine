#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>
#include <memory>
#include <sstream>
#include <iostream>

#include "../Helper/lodepng.h"
#include "../Helper/ILoggable.hpp"
#include "IDrawable.hpp"

class Texture : public IDrawable{
private:
	unsigned int id;
	std::string filename;
	bool loaded;
	std::string errorMsg;
	unsigned int width, height;
	size_t u2, v2;
	double u3, v3;
public:
	Texture(const char* filename):IDrawable(IDrawable::TEXTURE), filename(filename){
		//std::vector<unsigned char> image;
		std::vector<unsigned char> buffer;
		int error = lodepng::decode(buffer, width, height, filename);
		loaded = error == 0;

		std::ostringstream ss;
		if (loaded){
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(buffer[0]));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);

			ss << "<" << filename << "> loaded! (w: " << width << ", h:" << height << ", sz: " << buffer.size() << ", t:" << Type() << ", id: " << id << ")";
		} else {
			ss << "<"
			<< filename
			<< "> failed to load ("
			<< lodepng_error_text(error)
			<< ")";
		}
		errorMsg = ss.str();
		std::cout << errorMsg << std::endl;
		ss.clear();
		ss.str(std::string());

		/*
		// Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
		u2 = 1; while(u2 < width) u2 *= 2;
		std::cout << "w2: " << u2 << std::endl;
		v2 = 1; while(v2 < height) v2 *= 2;
		std::cout << "h2: " << u2 << std::endl;
		// Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
		u3 = (double)width / u2;
		std::cout << "w3: " << u2 << std::endl;
		v3 = (double)height / v2;
		std::cout << "h3: " << u2 << std::endl;

		std::vector<unsigned char> loader(u2 * v2 * 4);
		for(size_t y = 0; y < height; y++)
		for(size_t x = 0; x < width; x++)
		for(size_t c = 0; c < 4; c++)
		{
			loader[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
		}
		buffer.swap(image);
		*/
	};
	bool Loaded(){ return loaded; };
	unsigned int Width() { return width; }
	unsigned int Height() { return height; }
	size_t WidthS() { return u2; }
	size_t HeightS() { return v2; }
	double WidthD() { return u3; }
	double HeightD() { return v3; }
	std::string Filename() { return filename; }
	std::string ErrorMsg() { return errorMsg; }
	void Draw();
};

#endif // TEXTURE_HPP
