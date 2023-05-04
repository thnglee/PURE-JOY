#pragma once

#include<string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class BehaviorComponent : public Component {
	BehaviorComponent(std::string t) {
		tag = t;
	}
	~BehaviorComponent() {};

	void init() override {}

	void update() override {}


private:
	std::string tag;


};
