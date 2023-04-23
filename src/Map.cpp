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

	// need to read collision box according to "tag"

	/*for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			if (c == '1') {
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize); 
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}*/

}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos, std::string tID) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, tID);
	tile.addGroup(Game::groupMap);
}


