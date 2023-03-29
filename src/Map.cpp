#include "Map.h"
#include "game.h"
#include<fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"

extern Manager manager;

Map::Map(const char* mfp, int mscale, int tsize) : mapFilePath(mfp), mapScale(mscale), tileSize(tsize) {}
Map::~Map() {}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;


	if (mapFile) {
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

				AddTile(srcX, srcY, x * (tileSize * mapScale), y * (tileSize * mapScale));
				mapFile.ignore();
			}
		}
		mapFile.close();
	}
	else {
		std::cout << "Can not read file" << std::endl;
	}

	mapFile.ignore();
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			if (c == '1') {
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * (tileSize * mapScale), y * (tileSize * mapScale));
				mapFile.ignore();
			}
			mapFile.ignore();
		}
	}
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
	tile.addGroup(Game::groupMap);
}


