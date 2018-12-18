#include "Texture.hpp"

#include <stb_image/stb_image.h>

Texture::Texture(const std::string& path)
: id(0), filepath(path), width(0), height(0), bpp(0)
{
	std::cout << "Texture()" << std::endl;

	glCall(glGenTextures(1, &id));
	glCall(glBindTexture(GL_TEXTURE_2D, id));

	unsigned char* image;
	stbi_set_flip_vertically_on_load(1);
	image =
	stbi_load(
			path.c_str(),
			&width,
			&height,
			&bpp,
			4);
	/*
	int error = lodepng::decode(image, width, height, filepath);
	if (error == 0){
		std::cout << "<" << filepath << "> loaded" << std::endl;
		std::cout << "h: " << height << ", w: " << width << std::endl;
		std::cout << "s: " << image.size() << ", id: " << id << std::endl;
	} else {
		std::cout << "<" << filepath << "> failed" << std::endl;
	}
	*/

	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image));
	glCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (image){
		stbi_image_free(image);
	}
}

Texture::~Texture(){
	std::cout << "~Texture()" << std::endl;
	glCall(glDeleteTextures(1, &id));
}

void Texture::Bind(unsigned int slot) const {
	glCall(glActiveTexture(GL_TEXTURE0 + slot));
	glCall(glBindTexture(GL_TEXTURE_2D, id));
}

void Texture::Unbind() const {
	glCall(glBindTexture(GL_TEXTURE_2D, 0));
}
