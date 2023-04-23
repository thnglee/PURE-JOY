#pragma once

#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component {
	
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;
	std::string texID;

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id) {
		texID = id;
		texture = Game::assets->GetTexture(texID);

		position.x = static_cast<float>(xpos);
		position.y = static_cast<float>(ypos);
		
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.h = srcRect.w = tsize;

		//destRect.x = xpos;
		//destRect.y = ypos;
		destRect.w = destRect.h = tsize * tscale;
	}

	void update() override {
		if (texID == "water") {
			srcRect.x = srcRect.y = 0;
			srcRect.w = srcRect.h = 16;
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / 200) % 4);
		}
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};