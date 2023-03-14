#include "Map.h"
#include "game.h"
#include<fstream>

Map::~Map() {}

Map::Map() {}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	if (mapFile) {
		for (int y = 0; y < sizeY; y++) {
			for (int x = 0; x < sizeX; x++) {
				mapFile.get(tile);
				Game::AddTile(atoi(&tile), x * 16, y * 16);
				mapFile.ignore();
			}
		}
		mapFile.close();
	}
	else {
		std::cout << "Can not read file" << std::endl;
	}
}

