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
	unsigned int id; //, width, height, bpp;
	int width, height, bpp;
	std::string filepath;

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline unsigned int Width() const { return width; }
	inline unsigned int Height() const { return height; }
};
/*: public IDrawable{
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
		std::vector<unsigned char> image;
		int error = lodepng::decode(image, width, height, filename);
		loaded = error == 0;

		std::ostringstream ss;
		if (!loaded){
			ss << "<"
			<< filename
			<< "> failed to load ("
			<< lodepng_error_text(error)
			<< ")";
		} else {
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

			std::vector<unsigned char> image2(u2 * v2 * 4);
			for(size_t y = 0; y < height; y++)
			for(size_t x = 0; x < width; x++)
			for(size_t c = 0; c < 4; c++)
			{
				image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
			}

			/*
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(image2[0]));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			// Enable the texture for OpenGL.
			glCall(glEnable(GL_TEXTURE_2D));
			glCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)); //GL_NEAREST = no smoothing
			glCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			glCall(glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]));

			//glBindTexture(GL_TEXTURE_2D, 0);

			ss << "<" << filename << "> loaded! (w: " << width << ", h:" << height << ", sz: " << image.size() << ", t:" << Type() << ", id: " << id << ")";
		}
		errorMsg = ss.str();
		std::cout << errorMsg << std::endl;
		ss.clear();
		ss.str(std::string());

		//buffer.swap(image);
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
*/

#endif // TEXTURE_HPP
