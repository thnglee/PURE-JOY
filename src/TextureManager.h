#pragma once
#include "game.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);

private:

};
