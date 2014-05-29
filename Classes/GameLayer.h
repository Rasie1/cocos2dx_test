#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
USING_NS_CC;



enum
{
	COLLISION_EMPTY,
	COLLISION_FULL,
	COLLISION_BOTTOM,
	COLLISION_UP,
	COLLISION_LEFT,
	COLLISION_RIGHT,
	COLLISION_SMALL
};

enum
{
	TILE_NONE,
	TILE_GROUND,
	TILE_WALL
};

class MapGenerator
{
public:
	int getNextTile();

	MapGenerator() {}
};

class Tileset
{
public:
	std::string * textures;
	Tileset();

	/*std::string operator[](const int& i)
	{
		return textures[i];
	}*/
};

class MapInfo
{
public:
	Size size;
	Vec2 player_start;
	MapGenerator * generator;
	Tileset * tileset;
	int ** tiles;

	MapInfo(const Size size);
	~MapInfo();

	//returns type at [y][x]
	//int*& operator[](const int& y) { return array[y]; }

private:
};


class Terrain
{
public:
	MapInfo * map;
	//Vec2 playerPosition;
	//Vec2 cameraPosition;
	//Size & screenSize;
	Sprite ***  sprites;
	SpriteBatchNode ** batchNodes;


	void scroll(Vec2 delta);
	Terrain(MapInfo * currentMap);
	~Terrain() {}
};


/*
class Creature
{
public:
	int health;
	Vec2 moveVector;
};
*/


#endif
