#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;

	SDL_Rect srcRect = { 0,0,0,0 };

	bool animated = false;
	int frames = 1;
	int speed = 100;

public:
	SDL_Rect destRect = { 0,0,0,0 };

	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	//SpriteComponent(std::string id) {
	//	setTex(id);
	//}

	// Objects loading:
	SpriteComponent(std::string tag) {
		texture = Game::assets->GetTexture("grassbiom");
		if (tag == "small_rocks") {
			srcRect.x = 112;
			srcRect.y = 16;
		}
		else if (tag == "bushes") {
			srcRect.x = 16;
			srcRect.y = 48;
		}
		else if (tag == "big_trees") {
			srcRect.x = 0;
			srcRect.y = 0;
		}
		else if (tag == "big_rocks") {
			srcRect.x = 128;
			srcRect.y = 16;
		}
		else if (tag == "bushes_ripe") {
			srcRect.x = 0;
			srcRect.y = 48;
		}
		else if (tag == "big_trees_ripe") {
			srcRect.x = 32;
			srcRect.y = 0;
		}
		else if (tag == "small_trees") {
			srcRect.x = 64;
			srcRect.y = 0;
		}
	}

	SpriteComponent(std::string id, bool isAnimated) {
		animated = isAnimated;
		srcRect.x = srcRect.y = 0;

		Animation idle_down = Animation(0, 2, 500);
		Animation idle_up = Animation(1, 2, 500);
		Animation idle_right = Animation(2, 2, 500);
		Animation idle_left = Animation(3, 2, 500);

		Animation walk_down = Animation(4, 2, 250);
		Animation walk_up = Animation(5, 2, 250);
		Animation walk_right = Animation(6, 2, 250);
		Animation walk_left = Animation(7, 2, 250);

		animations.emplace("IdleDown", idle_down);
		animations.emplace("IdleUp", idle_up);
		animations.emplace("IdleRight", idle_right);
		animations.emplace("IdleLeft", idle_left);

		animations.emplace("WalkDown", walk_down);
		animations.emplace("WalkUp", walk_up);
		animations.emplace("WalkRight", walk_right);
		animations.emplace("WalkLeft", walk_left);

		Play("IdleDown");

		setTex(id);
	}
	

	~SpriteComponent() {
		// SDL_DestroyTexture(texture);
	}
	
	void setTransparency(int value) {
		SDL_SetTextureAlphaMod(texture, value);
	}

	void setTex(std::string id) {
		texture = Game::assets->GetTexture(id);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
			srcRect.y = animIndex * transform->height;
		}

		destRect.x = static_cast<float>(transform->position.x - Game::camera.x);
		destRect.y = static_cast<float>(transform->position.y - Game::camera.y);

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip); 
	}
	
	void Play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};