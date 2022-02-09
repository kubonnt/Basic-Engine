#pragma once
#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <iostream>
#include <string>
#include <stb_image.h>

#include <glad/glad.h>

/*
	TODO:
		Move that code to shader header because it is useless to write a separate header and cpp file for such thing
*/

struct TextureLoader
{
	static unsigned int loadAndGenerateTexture(const char* filePath);
};
#endif
