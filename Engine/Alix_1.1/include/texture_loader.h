#pragma once
#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <iostream>
#include <stb_image.h>

#include <glad/glad.h>


struct TextureLoader
{
	static unsigned int loadAndGenerateTexture(const char* filePath);
};
#endif
