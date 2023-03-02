#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y) 
{
	objTexture = TextureManager::LoadTexture(textureSheet);
	
	xpos = x;
	ypos = y;
} 

void GameObject::Update() {
	xpos++;
	ypos++;

	srcRect.h = 32; // pixel inside the spritesheet file
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos; // pixel in the window
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}