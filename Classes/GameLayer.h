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
	//Vector<Creature> creatures;


	SpriteBatchNode ** batchNodes;


	void scroll(Vec2 delta);
	void update();

	MainLayer(MapInfo * currentMap);
	~MainLayer() {}
	static MainLayer * create(MapInfo * currentMap);
private:
	Vec2 _renderingCenterPosition, _cameraCenterPosition;
};



class Creature : public Sprite
{
public:
	int health;
	Size boundingBox;
	Vec2 moveVector;
	void MoveTo(Vec2 target);
	void MoveBy(Vec2 delta);
	Creature(Vec2 pos);
    static Creature* create(Vec2 pos);

};
/*
class Player : public Creature
{
public:
	Player();
	static Player* create();
};
*/

#endif
