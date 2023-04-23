#pragma once
#include<string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {
public:
 
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;

	SDL_Rect srcR, destR;

	TransformComponent* transform;

	ColliderComponent(std::string t) {
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size) {
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}
	
	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("assets/blankTile/1x1.png");

		srcR.x = srcR.y = 0;
		srcR.w = srcR.h = 1;
		
		destR.x = collider.x;
		destR.y = collider.y;
		destR.w = destR.h = collider.w;

	}

	void update() override {
		if (tag == "player") {
			collider.x = static_cast<int>(transform->position.x + 2 * transform->scale);
			collider.y = static_cast<int>(transform->position.y + 12 * transform->scale);
			collider.w = transform->width * transform->scale * 3 / 4;
			collider.h = transform->height * transform->scale / 4;
		}
	
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;
	}

	void draw() override {
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};