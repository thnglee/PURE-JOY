#include "game.h"
#include "TextureManager.h"	
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 1600, 900};

std::vector<ColliderComponent*> Game::colliders;
bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

const char* water = "assets/tilesets/water.png";
const char* grass = "assets/tilesets/grass.png";
const char* grass_hill_2 = "assets/tilesets/grass_hill_(2).png";
const char* wood_bridge = "assets/objects/wood_bridge.png";
const char* grass_hill_3 = "assets/tilesets/grass_hill_(3).png";
const char* dirt = "assets/tilesets/dirt.png";

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

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


	map = new Map();

	// ecs implementation:

	Map::LoadMap("map/map_v1.2/island_v1_water.csv", 50, 50, water);
	Map::LoadMap("map/map_v1.2/island_v1_grass.csv", 50, 50, grass);
	Map::LoadMap("map/map_v1.2/island_v1_dirt.csv", 50, 50, dirt);
	Map::LoadMap("map/map_v1.2/island_v1_grass_hill_(3).csv", 50, 50, grass_hill_3);
	Map::LoadMap("map/map_v1.2/island_v1_grass_hill_(2).csv", 50, 50, grass_hill_2);
	Map::LoadMap("map/map_v1.2/island_v1_wood_bridge.csv", 50, 50, wood_bridge);

	player.addComponent<TransformComponent>(1600, 900, 16, 16, 4);
	player.addComponent<SpriteComponent>("assets/characters/character.png", true);
	player.getComponent<TransformComponent>().position.x = 250;
	player.getComponent<TransformComponent>().position.y = 250;
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
}


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

void Game::update() {
	manager.refresh();
	manager.update();

	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 800);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 450);

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x + camera.w > 16 * 4 * 50) camera.x = 16 * 4 * 50 - camera.w;
	if (camera.y + camera.h > 16 * 4 * 50) camera.y = 16 * 4 * 50 - camera.h;
}


void Game::render() {
	SDL_RenderClear(renderer);

	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	for (auto& e : enemies) {
		e->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos, const char* layerPath) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, layerPath);
	tile.addGroup(groupMap);
}
