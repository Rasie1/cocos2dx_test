#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "actor.h"
USING_NS_CC;

class Actor;
class Creature;

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
	int getNextObject();

	MapGenerator() {}
};

class Tileset
{
public:
	std::vector<std::string> textures;
	Tileset();

	/*std::string operator[](const int& i)
	{
		return textures[i];
	}*/
};

class MapInfo
{
public:
	Size mapSize;
	int tileSize;
	Vec2 playerStart;
	MapGenerator * generator;
	Tileset * tileset;
	int ** tiles;
	int ** actors;


	MapInfo(const Size size);
	~MapInfo();

	//returns type at [y][x]
	//int*& operator[](const int& y) { return array[y]; }

private:
};



class MainLayer : public Layer
{
public:
	MapInfo * map;
	//Vec2 playerPosition;
	//Vec2 cameraPosition;
	//Size & screenSize;
	Sprite ***  terrain;
	Vector< Actor*> actors;
	Vector< Actor*> localActors;
	Creature * cr;
	//Player * player;

	SpriteBatchNode ** batchNodes;


	void scroll(Vec2 delta);
	void update();

	MainLayer(MapInfo * currentMap);
	~MainLayer() {}
	static MainLayer * create(MapInfo * currentMap);
private:
	Vec2 _renderingCenterPosition, _cameraCenterPosition;
};



#endif
