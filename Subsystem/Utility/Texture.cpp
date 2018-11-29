#include "Texture.hpp"

void Texture::Draw(){
	/*
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &buffer[0]);
	glColor4ub(255, 255, 255, 255);

	glBegin(GL_QUADS);
		glTexCoord2d(0, 0);	glVertex2f(0, 0);
		glTexCoord2d(u3,0); glVertex2f(width, 0);
		glTexCoord2d(u3, v3); glVertex2f(width, height);
		glTexCoord2d(0, v3); glVertex2f(0, height);
	glEnd();
	*/
	/*
	glRasterPos2i(0, 0);
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, &buffer[0]);
	*/
}
