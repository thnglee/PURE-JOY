#include "Map.h"
#include "game.h"
#include<fstream>

Map::~Map() {}
Map::Map() {}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	if (mapFile) {
		for (int y = 0; y < sizeY; y++) {
			for (int x = 0; x < sizeX; x++) {
				mapFile.get(c);
				srcY = atoi(&c) * 16;

				mapFile.get(c);
				srcX = atoi(&c) * 16;

				Game::AddTile(srcX, srcY, x * 16 * 4, y * 16 * 4);
				mapFile.ignore();
			}
		}
		mapFile.close();
	}
	else {
		std::cout << "Can not read file" << std::endl;
	}
}

