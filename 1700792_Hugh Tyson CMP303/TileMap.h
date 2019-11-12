// Map Class
// Builds and store level sections based on TileMap and TileSet

#pragma once
#include <math.h>
#include "MySprite.h"

class TileMap
{
public:
	TileMap();
	~TileMap();

	void loadTexture(char* filename);
	void setTileSet(std::vector<MySprite> ts);
	void setTileMap(std::vector<int> tm, sf::Vector2u mapDimensions);
	void buildLevel();

	void render(sf::RenderWindow* window);
	std::vector<MySprite>* getLevel(){ return &level; };

	void setPosition(sf::Vector2f pos) { position = pos; };

protected:
	std::vector<MySprite> tileSet;
	std::vector<int> tileMap;
	std::vector<MySprite> level;
	sf::Texture texture;
	sf::Vector2u mapSize;
	sf::Vector2f position;
};

