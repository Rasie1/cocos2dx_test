#include "GameLayer.h"
#include "actor.h"

USING_NS_CC;


Tileset::Tileset()
{
	textures.push_back("tile3.png");
	textures.push_back("tile5.png");
	textures.push_back("tile6.png");
}

int MapGenerator::getNextTile()
{
	return (rand() % 4) ? 0 : ((rand() % 2) + 1);
}

int MapGenerator::getNextObject()
{
	return (rand() % 100) ? 0 : 1;
}

MapInfo::MapInfo(const Size size)
{
	this->mapSize = size;
	this->tileSize = 64;
	this->playerStart = Vec2(1, 1);
	tiles = new int*[(int)size.height];
	actors = new int*[(int)size.height];
	tileset = new Tileset();
	generator = new MapGenerator();
	for (int i = 0; i < size.height; ++i)
	{
		tiles[i] = new int[(int)size.width];
		actors[i] = new int[(int)size.width];
		for (int j = 0; j < size.width; ++j)
		{
			tiles[i][j] = generator->getNextTile();
			actors[i][j] = generator->getNextObject();
		}
	}
}

MainLayer::MainLayer(MapInfo * currentMap)
{
	map = currentMap;
	terrain = new Sprite**[(int)map->mapSize.height];
	Size screenSize = Director::getInstance()->getWinSize();
	//batchNodes = new SpriteBatchNode*[map->tileset->textures.size()];
	this->setAnchorPoint(map->playerStart);
	_cameraCenterPosition = map->playerStart;
	/*for (int i = 0; i < map->tileset->textures.size(); ++i)
	{
		batchNodes[i] = SpriteBatchNode::create(map->tileset->textures[i]);
		this->addChild(batchNodes[i]); //batchnode children maximum is 16384
	}*/

	for (int i = 0; i < map->mapSize.height; ++i)
	{
		terrain[i] = new Sprite*[(int)map->mapSize.width];
		for (int j = 0; j < map->mapSize.width; ++j)
		{
			terrain[i][j] = Sprite::create(map->tileset->textures[(map->tiles[i][j])]);
			terrain[i][j]->setVisible(false);
			terrain[i][j]->setPosition(Vec2((j+i)*64, (j-i)*32));
			if (map->actors[i][j])
			{
				this->actors.pushBack(Actor::create(Vec2(i, j), this));
				this->addChild(actors.back(), 999);
			}
			this->addChild(terrain[i][j], i - j);
			//batchNodes[map->tiles[i][j]]->addChild(sprites[i][j], i - j);
		}
	}
	update();
}

MainLayer * MainLayer::create(MapInfo * currentMap)
{
	MainLayer *ret = new MainLayer(currentMap);
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}
MapInfo::~MapInfo()
{

}

void MainLayer::scroll(Vec2 delta)
{
	this->setPosition(this->getPosition() + delta);
	_cameraCenterPosition = this->getPosition();
}

void MainLayer::update()
{
	if (abs(_cameraCenterPosition.x - _renderingCenterPosition.x) < 5 && abs(_cameraCenterPosition.y - _renderingCenterPosition.y) < 5)
		return;
	else
		_renderingCenterPosition = _cameraCenterPosition;
	const Vec2 x_renderingCenterPosition = _renderingCenterPosition - Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	int _x = -x_renderingCenterPosition.y / 64 - x_renderingCenterPosition.x / 128;
	int _y = -x_renderingCenterPosition.x / 128 + x_renderingCenterPosition.y / 64;
	int wx = map->mapSize.width;
	int wy = map->mapSize.height;
	for (int i = _y - 15; i < _y + 15; ++i)
	for (int j = _x - 15; j < _x + 15; ++j)
	{
		if (i >= 0 && j >= 0 && j < wx && i < wy)
		{
			int ci = i - _y;
			int cj = j - _x;
			if (ci*ci + cj*cj < 84)
				this->terrain[i][j]->setVisible(true);
			else
				this->terrain[i][j]->setVisible(false);
		}
	}
}
