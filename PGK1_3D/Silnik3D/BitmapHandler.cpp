#include "BitmapHandler.hpp"

void  BitmapHandler::load(char* name) {
	BitmapHandler::dt = stbi_load(name, &BitmapHandler::width, &BitmapHandler::height, &BitmapHandler::nchan, 0);
	if (!dt) exit(0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BitmapHandler::width, BitmapHandler::height,0, GL_RGB, GL_UNSIGNED_BYTE, BitmapHandler::dt);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	stbi_image_free(BitmapHandler::dt);

}