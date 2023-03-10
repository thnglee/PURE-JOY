#include "Map.h"
#include "TextureManager.h"

int farm[25][25] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},	
	{0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,2,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,0},
	{0,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,0},
	{0,1,1,1,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0},
	{0,1,1,1,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::~Map() {
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(water);
	SDL_DestroyTexture(dirt);
}

Map::Map() {
	dirt = TextureManager::LoadTexture("assets/Tilesets/ground_tiles/old_tiles/tilled_dirt.png");
	grass = TextureManager::LoadTexture("assets/Tilesets/ground_tiles/old_tiles/Grass.png");
	water = TextureManager::LoadTexture("assets/Tilesets/Water.png");

	LoadMap(farm);

	src.x = src.y = 0;
	// src.w = dest.w = 16;
	// src.h = dest.h = 16;

	src.w = src.h = 16;
	dest.w = dest.h = 64;

	dest.x = dest.y = 0;
}

void Map::LoadMap(int arr[25][25]) {
	for (int row = 0; row < 25; row++) {
		for (int column = 0; column < 25; column++) {
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap() {
	int type = 0;

	for (int row = 0; row < 25; row++) {
		for (int column = 0; column < 25; column++) {
			type = map[row][column];

			dest.x = column * 16 * 3;
			dest.y = row * 16 * 3;

			switch (type)
			{
			case 0:
				TextureManager::Draw(water, src, dest);
				break;

			case 1: 
				TextureManager::Draw(grass, src, dest);
				break;

			case 2:
				TextureManager::Draw(dirt, src, dest);
				break;

			default:
				break;
			}
		}
	}
}