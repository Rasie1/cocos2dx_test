#include "GameLayer.h"

USING_NS_CC;


Tileset::Tileset()
{
	textures.push_back("tile3.png");
	textures.push_back("tile5.png");
	textures.push_back("tile6.png");
}

int MapGenerator::getNextTile()
{
	return (rand()%2)?0:((rand()%2) + 1);
}



MapInfo::MapInfo(const Size size)
{
	this->mapSize = size;
	this->tileSize = 64;
	this->playerStart = Vec2(20, 20);
	tiles = new int*[(int)size.height];
	tileset = new Tileset();
	generator = new MapGenerator();
	for (int i = 0; i < size.height; ++i)
	{
		tiles[i] = new int[(int)size.width];
		for (int j = 0; j < size.width; ++j)
		{
			tiles[i][j] = generator->getNextTile();
		}
	}
}

MainLayer::MainLayer(MapInfo * currentMap)
{
	map = currentMap;
	terrain = new Sprite**[(int)map->mapSize.height];
	Size screenSize = Director::getInstance()->getWinSize();
	Vec2 center = Vec2(screenSize.width / 2, screenSize.height / 2);
	this->setPosition(center);
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
			terrain[i][j]->setPosition(Vec2((j+i)*64, (j-i)*32) + center);
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
	int _x = -_renderingCenterPosition.y / 64 - _renderingCenterPosition.x / 128;
	int _y = - _renderingCenterPosition.x / 128 + _renderingCenterPosition.y / 64;
	int wx = map->mapSize.width;
	int wy = map->mapSize.height;
	for (int i = _y - 15; i < _y + 15; ++i)
	for (int j = _x - 15; j < _x + 15; ++j)
	{
		if (i>=0 && j >=0 && j < wx && i < wy) this->terrain[i][j]->setVisible(false);
	}
	for (int i = _y - 10; i < _y + 10; ++i)
	for (int j = _x - 10; j < _x + 10; ++j)
	{
		if (i >= 0 && j >= 0 && j < wx && i < wy) this->terrain[i][j]->setVisible(true);
	}
}

Creature::Creature(Vec2 pos)
{
	this->initWithFile("blank.png");
	this->setTextureRect(cocos2d::Rect(0,0,400,500));
	this->setColor(Color3B(255,255,255));
	this->setPosition(Vec2((pos.x+pos.y)*64, (pos.x-pos.y)*32));
}

Creature* Creature::create(Vec2 pos)
{
    Creature *sprite = new (std::nothrow) Creature(pos);
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}



void Creature::MoveTo(Vec2 target)
{
	this->runAction(MoveTo::create(4, Vec2(rand()%400,rand()%400)));
}

void Creature::MoveBy(Vec2 delta)
{

}

/*
Player* Player::create()
{
    Player *sprite = new (std::nothrow) Player();
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Player::Player()
{

}*/
