#include "Texture.hpp"

void Texture::Close(){
	std::cout << "~Texture()" << std::endl;
	glCall(glDeleteTextures(1, &id));
}

void Texture::Init(const std::string& path){
	this->filepath = path;
	std::cout << "Texture()" << std::endl;

	glCall(glGenTextures(1, &id));
	glCall(glBindTexture(GL_TEXTURE_2D, id));

	unsigned char* image;
	//stbi_set_flip_vertically_on_load(1);
	image =
	stbi_load(
			path.c_str(),
			&width,
			&height,
			&bpp,
			4);

	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image));
	glCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (image){
		stbi_image_free(image);
	}

	std::cout << "<" << path << "> " << (image? "loaded!" : "failed to load!") << std::endl;
}

void Texture::Bind(unsigned int slot) const {
	glCall(glActiveTexture(GL_TEXTURE0 + slot));
	glCall(glBindTexture(GL_TEXTURE_2D, id));
}

void Texture::Unbind() const {
	glCall(glBindTexture(GL_TEXTURE_2D, 0));
}
