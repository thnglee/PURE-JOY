#include "Map.h"
#include "game.h"
#include<fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"


extern Manager manager;

Map::Map(int mscale, int tsize){
	mapScale = mscale;
	tileSize = tsize;
	scaledSize = mscale * tsize;
}

Map::Map(int mscale) {
	mapScale = mscale;
}

Map::~Map() {}

void Map::LoadMap(std::string path, int sizeX, int sizeY, std::string tID) {
	texID = tID;
	
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	if (mapFile) {
		if (texID == "wall") {
			for (int y = 0; y < sizeY; y++) {
				for (int x = 0; x < sizeX; x++) {
					mapFile.get(c);
					if (c == '-') {
						mapFile.get(c);
						mapFile.ignore();
						continue;
					}
					if (c == '0') {
						auto& tcol(manager.addEntity());
						tcol.addComponent<ColliderComponent>("wall", x * scaledSize,y * scaledSize, scaledSize);
						tcol.addGroup(Game::groupColliders);
					}
					mapFile.ignore();
				}
			}
		}
		else {
			for (int y = 0; y < sizeY; y++) {
				for (int x = 0; x < sizeX; x++) {
					mapFile.get(c);
					if (c == '-') {
						mapFile.get(c);
						mapFile.ignore();
						continue;
					}
					srcY = atoi(&c) * tileSize;
					mapFile.get(c);
					srcX = atoi(&c) * tileSize;

					AddTile(srcX, srcY, x * scaledSize, y * scaledSize, texID);
					mapFile.ignore();
				}
			}
			mapFile.close();
		}
	}
	else {
		std::cout << "Can not read file" << std::endl;
	}
}

void Map::LoadObjects(std::string path, std::string tag) {
	
	std::fstream CoordinateFile;
	CoordinateFile.open(path);

	float destX, destY;
	if (CoordinateFile) {
		while (!CoordinateFile.eof())
		{
			CoordinateFile >> destX; 
			CoordinateFile.ignore();
			CoordinateFile >> destY;
			CoordinateFile.ignore();

			if (tag == "small_rocks" || tag == "bushes" || tag == "bushes_ripe" ||
				tag == "big_rocks") {
				destY -= 16;
			}
			else if (tag == "big_trees" || tag == "small_trees" || tag == "big_trees_ripe") {
				destY -= 32;
			}
			AddObjects(destX * mapScale, destY * mapScale, tag);
		}
	}
	else {
		std::cout << "Can not read file" << std::endl;
	}
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos, std::string tID) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, tID);
	tile.addGroup(Game::groupMap);
}

void Map::AddObjects(float destX, float destY, std::string tag) {
	auto& object(manager.addEntity());
	int sizeX, sizeY;
	if (tag == "small_rocks" || tag == "bushes" || tag == "bushes_ripe" ||
		tag == "big_rocks") {
		sizeX = sizeY = 16;
	}
	else if (tag == "big_trees" || tag == "big_trees_ripe") {
		sizeX = sizeY = 32;
	}
	else if (tag == "small_trees") {
		sizeX = 16;
		sizeY = 32;
	}

	object.addComponent<TransformComponent>(destX, destY, sizeX, sizeY, mapScale);
	object.addComponent<SpriteComponent>(tag);
	object.addComponent<ColliderComponent>(tag);
	//object.addGroup(Game::groupColliders);
	object.addGroup(Game::groupObjects);
}