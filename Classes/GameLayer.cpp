#include "GameLayer.h"

USING_NS_CC;


Tileset::Tileset()
{
	textures = new std::string[2];
	textures[0] = "tile1.png";
	textures[1] = "tile2.png";
}

int MapGenerator::getNextTile()
{
	return !bool(rand()%5);
}



MapInfo::MapInfo(const Size size)
{
	this->size = size;
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
	sprites = new Sprite**[(int)map->size.height];
	batchNodes = new SpriteBatchNode*[sizeof(map->tileset->textures)];
	batchNodes[0] = SpriteBatchNode::create(map->tileset->textures[0]);
	this->addChild(batchNodes[0]);
	batchNodes[1] = SpriteBatchNode::create(map->tileset->textures[1]);
	this->addChild(batchNodes[1]);

	for (int i = 0; i < map->size.height; ++i)
	{
		sprites[i] = new Sprite*[(int)map->size.width];
		for (int j = 0; j < map->size.width; ++j)
		{
			sprites[i][j] = Sprite::create(map->tileset->textures[(map->tiles[i][j])]);
			sprites[i][j]->setPosition(Vec2(j*32, ((map->size.height + j) * 16 - i * 32)));
			batchNodes[map->tiles[i][j]]->addChild(sprites[i][j], -j - i);
		}
	}
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

}