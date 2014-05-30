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

Terrain::Terrain(MapInfo * currentMap)
{
	map = currentMap;
	sprites = new Sprite**[(int)map->mapSize.height];
	Size screenSize = Director::getInstance()->getWinSize();
	Vec2 center = Vec2(screenSize.width / 2, screenSize.height / 2);
	batchNodes = new SpriteBatchNode*[map->tileset->textures.size()];
	this->setAnchorPoint(map->playerStart);
	_cameraCenterPosition = map->playerStart;
	for (int i = 0; i < map->tileset->textures.size(); ++i)
	{
		batchNodes[i] = SpriteBatchNode::create(map->tileset->textures[i]);
		this->addChild(batchNodes[i]); //batchnode children maximum is 16384
	}

	for (int i = 0; i < map->mapSize.height; ++i)
	{
		sprites[i] = new Sprite*[(int)map->mapSize.width];
		for (int j = 0; j < map->mapSize.width; ++j)
		{
			sprites[i][j] = Sprite::create(map->tileset->textures[(map->tiles[i][j])]); 
			sprites[i][j]->setVisible(false);
			sprites[i][j]->setPosition(Vec2((j+i)*64, (j-i)*32));

			batchNodes[map->tiles[i][j]]->addChild(sprites[i][j], i - j);
		}
	}
	update();
}

Terrain * Terrain::create(MapInfo * currentMap)
{
	Terrain *ret = new Terrain(currentMap);
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

void Terrain::scroll(Vec2 delta)
{
	this->setPosition(this->getPosition() + delta);
	_cameraCenterPosition = this->getPosition();
}

void Terrain::update()
{
	if (abs(_cameraCenterPosition.x - _renderingCenterPosition.x) < 5 && abs(_cameraCenterPosition.y - _renderingCenterPosition.y) < 5)
		return;
	else
		_renderingCenterPosition = _cameraCenterPosition;
	int _x = _renderingCenterPosition.x / 128 + _renderingCenterPosition.y / 64;
	int _y = _renderingCenterPosition.y / 64 - _renderingCenterPosition.x / 128;
	for (int i = _y - 20; i < _y + 20; ++i)
	for (int j = _x - 20; j < _x + 20; ++j)
	{
		if (i>=0 && j >=0) this->sprites[i][j]->setVisible(false);
	}
	for (int i = _y - 5; i < _y + 5; ++i)
	for (int j = _x - 5; j < _x + 5; ++j)
	{
		if (i >= 0 && j >= 0) this->sprites[i][j]->setVisible(true);
	}
}