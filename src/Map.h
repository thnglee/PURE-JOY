#pragma once
#include<string>

class Map {
public:	
	Map(int mscale, int tsize);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY, std::string tID);
	void AddTile(int srcX, int srcY, int xpos, int ypos, std::string tID);

private:
	std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;
};	