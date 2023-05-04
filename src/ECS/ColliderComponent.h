#pragma once
#include<string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"
#include "Collision.h"
#include "game.h"

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

		if (tag == "wall") {
			transform->position.x = collider.x;
			transform->position.y = collider.y;
		}
		tex = TextureManager::LoadTexture("assets/blankTile/1x1.png");

		srcR.x = srcR.y = 0;
		srcR.w = srcR.h = 1;

		/*destR.x = collider.x;
		destR.y = collider.y;
		destR.w = destR.h = collider.w;*/
	}

	void update() override {
		if (tag == "wall") {
			collider.x = static_cast<int>(transform->position.x) - Game::camera.x;
			collider.y = static_cast<int>(transform->position.y) - Game::camera.y;
		}
		else if (tag == "player") {
			collider.x = static_cast<int>(transform->position.x + 4 * transform->scale) - Game::camera.x;
			collider.y = static_cast<int>(transform->position.y + 12 * transform->scale) - Game::camera.y;
			collider.w = transform->width * transform->scale * 2 / 4;
			collider.h = transform->height * transform->scale / 4;
		}
		else if (tag == "big_rocks") {
			collider.x = static_cast<int>(transform->position.x + 2 * transform->scale) - Game::camera.x;
			collider.y = static_cast<int>(transform->position.y + 7 * transform->scale) - Game::camera.y;
			collider.w = 12 * transform->scale;
			collider.h = 5 * transform->scale;
		}
		else if (tag == "big_trees" || tag == "big_trees_ripe") {
			collider.x = static_cast<int>(transform->position.x + 12 * transform->scale) - Game::camera.x;
			collider.y = static_cast<int>(transform->position.y + 27 * transform->scale) - Game::camera.y;
			collider.w = 8 * transform->scale;
			collider.h = 3 * transform->scale;
		}
		else if (tag == "bushes" || tag == "bushes_ripe") {
			collider.x = static_cast<int>(transform->position.x + 1 * transform->scale) - Game::camera.x;
			collider.y = static_cast<int>(transform->position.y + 9 * transform->scale) - Game::camera.y;
			collider.w = 14 * transform->scale;
			collider.h = 5 * transform->scale;
		}
		else if (tag == "small_rocks") {
			collider.x = static_cast<int>(transform->position.x + 4 * transform->scale) - Game::camera.x;
			collider.y = static_cast<int>(transform->position.y + 6 * transform->scale) - Game::camera.y;
			collider.w = 6 * transform->scale;
			collider.h = 2 * transform->scale;
		}
		else if (tag == "small_trees") {
			collider.x = static_cast<int>(transform->position.x + 5 * transform->scale) - Game::camera.x;
			collider.y = static_cast<int>(transform->position.y + 24 * transform->scale) - Game::camera.y;
			collider.w = 6 * transform->scale;
			collider.h = 3 * transform->scale;
		}
		
		destR.x = collider.x;
		destR.y = collider.y;
		destR.w = collider.w;
		destR.h = collider.h;
	}	

	void draw() override {
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};