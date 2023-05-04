#pragma once
#include<string>

class Map {
public:	
	Map(int mscale, int tsize);
	Map(int mscale);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY, std::string tID);
	void AddTile(int srcX, int srcY, int xpos, int ypos, std::string tID);

	void LoadObjects(std::string path, std::string tag);
	void AddObjects(float destX, float destY, std::string tag);


private:
	std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;
};	