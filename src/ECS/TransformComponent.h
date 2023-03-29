#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {

public:
	
	Vector2D position;
	Vector2D velocity;
	Vector2D direction;

	int height = 16;
	int width = 16;
	int scale = 1;

	int speed = 4;	

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(int sc) {
		position.x = 800;
		position.y = 450;
		scale = sc;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int w, int h, int sc) {
		direction.y = 1;
		direction.x = 0;

		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = sc;
	}

	bool isIdle() {
		return (velocity.x == 0 && velocity.y == 0);
	}

	void init() override {
		velocity.Zero();
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};