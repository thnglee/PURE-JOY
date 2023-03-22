#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		transform->velocity.x = 0;
		transform->velocity.y = 0;
		sprite->Play("IdleDown");

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_W]) {
			transform->velocity.y = -1;
			sprite->Play("WalkUp");
		}
		if (currentKeyStates[SDL_SCANCODE_A]) {
			transform->velocity.x = -1;
			sprite->Play("WalkLeft");
		}
		if (currentKeyStates[SDL_SCANCODE_D]) {
			transform->velocity.x = 1;
			sprite->Play("WalkRight");
		}
		if (currentKeyStates[SDL_SCANCODE_S]) {
			transform->velocity.y = 1;
			sprite->Play("WalkDown");
		}
		if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
			Game::isRunning = false;
		}

		/*if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				if (transform->velocity.x == 0) sprite->Play("WalkUp");
				break;

			case SDLK_a:
				transform->velocity.x = -1;
				if (transform->velocity.y == 0) sprite->Play("WalkLeft");
				break;

			case SDLK_d:
				transform->velocity.x = 1;
				if (transform->velocity.y == 0) sprite->Play("WalkRight");
				break;
				
			case SDLK_s:
				transform->velocity.y = 1;
				if (transform->velocity.x == 0) sprite->Play("WalkDown");
				break;


			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				if (transform->velocity.x == 0) sprite->Play("IdleUp");
				break;

			case SDLK_a:
				transform->velocity.x = 0;
				if (transform->velocity.y == 0) sprite->Play("IdleLeft");
				break;

			case SDLK_d:
				transform->velocity.x = 0;
				if (transform->velocity.y == 0) sprite->Play("IdleRight");
				break;

			case SDLK_s:
				transform->velocity.y = 0;
				if (transform->velocity.x == 0) sprite->Play("IdleDown");
				break;

			case SDLK_ESCAPE:
				Game::isRunning = false;

			default:
				break;
			}
		}*/
	}
};