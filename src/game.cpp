#include "game.h"
#include "TextureManager.h"	
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include<sstream>

// init value:
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;

// map init and scale:
Map* terrain;
Map* CollisionBox;
Map* objects;
int default_scale = 4;

// adding entities:
Manager manager;
auto& player(manager.addEntity());
AssetManager* Game::assets = new AssetManager(&manager);
SDL_Rect Game::camera = {0, 0, 1600, 900};

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	// game init:
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		SDL_SetWindowBordered(window, SDL_FALSE);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}

	// player texture:
	assets->AddTexture("player", "assets/characters/character.png");

	// terrain textures:
	assets->AddTexture("water", "assets/tilesets/water.png");
	assets->AddTexture("grass", "assets/tilesets/grass.png");
	assets->AddTexture("grass_patterns", "assets/tilesets/grass.png");
	assets->AddTexture("dirt", "assets/tilesets/dirt.png");
	assets->AddTexture("grass_hill", "assets/tilesets/grass_hill_(3).png");
	assets->AddTexture("grass_island", "assets/tilesets/grass_hill_(2).png");
	assets->AddTexture("wood_bridge", "assets/objects/wood_bridge.png");
	assets->AddTexture("grassbiom", "assets/objects/grassbiom.png");

	// wall texture: [collision box]
	assets->AddTexture("wall", "assets/blankTile/1x1.png");

	// map textures loading: 
	terrain = new Map(4, 16);
	terrain->LoadMap("map/map_v1.4/island_v1.4_water.csv", 50, 50, "water");
	terrain->LoadMap("map/map_v1.4/island_v1.4_grass.csv", 50, 50, "grass");
	terrain->LoadMap("map/map_v1.4/island_v1.4_grass_hill_(3).csv", 50, 50, "grass_hill");
	terrain->LoadMap("map/map_v1.4/island_v1.4_grass_hill_(2).csv", 50, 50, "grass_island");
	terrain->LoadMap("map/map_v1.4/island_v1.4_grass_patterns.csv", 50, 50, "grass_patterns");
	terrain->LoadMap("map/map_v1.4/island_v1.4_wood_bridge.csv", 50, 50, "wood_bridge");
	terrain->LoadMap("map/map_v1.4/island_v1.4_dirt.csv", 50, 50, "dirt");
	terrain->LoadMap("map/map_v1.4/island_v1.4_grassbiom.csv", 50, 50, "grassbiom");
	//terrain->LoadMap("map/map_v1.3/island_v1_blank_collision_box.csv", 50, 50, "wall");

	// Map collision loading: 
	CollisionBox = new Map(4, 1);
	CollisionBox->LoadMap("map/map_v1.4/1x1_collision_box_1x1.csv", 800, 800, "wall");

	// Objects adding and loading (fuck sake):
	objects = new Map(4);
	objects->LoadObjects("map/map_v1.4/lua for objects/small_rocks.csv", "small_rocks");
	objects->LoadObjects("map/map_v1.4/lua for objects/bushes.csv", "bushes");
	objects->LoadObjects("map/map_v1.4/lua for objects/big_trees.csv", "big_trees");
	objects->LoadObjects("map/map_v1.4/lua for objects/big_trees_ripe.csv", "big_trees_ripe");
	objects->LoadObjects("map/map_v1.4/lua for objects/big_rocks.csv", "big_rocks");
	objects->LoadObjects("map/map_v1.4/lua for objects/bushes_ripe.csv", "bushes_ripe");
	objects->LoadObjects("map/map_v1.4/lua for objects/small_trees.csv", "small_trees");

	// init player:
	player.addComponent<TransformComponent>(450, 450, OBJECT_WIDTH, OBJECT_HEIGHT, default_scale);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
}

// grouping entities:
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& gameobjects(manager.getGroup(Game::groupObjects));

// handling events:
void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

// updating the game:
void Game::update() {
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;

	manager.refresh();
	manager.update();

	SDL_Rect objectCol;
	for (auto& o : gameobjects) {
		objectCol = o->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(playerCol, objectCol)) {
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	// colliding tracking:
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	// projectile hitting tracking:
	for (auto& p : projectiles) {
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider)) {
			std::cout << "Hit player !" << std::endl;
			p->destroy();
		}
	}

	// camera following player:
	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x + OBJECT_WIDTH * default_scale / 2 - WINDOW_WIDTH / 2);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y + OBJECT_HEIGHT * default_scale / 2 - WINDOW_HEIGHT / 2);
	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > MAP_WIDTH * default_scale - camera.w) camera.x = MAP_WIDTH * default_scale - camera.w;
	if (camera.y > MAP_HEIGHT * default_scale - camera.h) camera.y = MAP_HEIGHT * default_scale - camera.h;

}

// screen rendering:
void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles) t->draw();


	bool isOverlaying = false;
	SDL_Rect fullsprite, objectCol;
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	for (auto& o : gameobjects) {
		fullsprite = o->getComponent<SpriteComponent>().destRect;
		objectCol = o->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(playerCol, fullsprite) &&
			playerCol.y < objectCol.y) {
			isOverlaying = true;
		}
	}

	if (isOverlaying) {
		for (auto& p : players) p->draw();
		for (auto& o : gameobjects) o->draw();
	}
	else {
		for (auto& o : gameobjects) o->draw();
		for (auto& p : players) p->draw();
	}

	for (auto& c : colliders) c->draw();

	SDL_RenderPresent(renderer);
}

// clean up the mess:
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

