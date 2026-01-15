#pragma once

#include <GL/freeglut.h>
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"class BitmapHandler {public:	int width=0, height=0, nchan=0;	unsigned char* dt=0;	BitmapHandler();private:	void load(char * name);};