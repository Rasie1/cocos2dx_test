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
	return 0;
}



MapInfo::MapInfo(const Size size)
{
	this->size = size;
	tiles = new int*[(int)size.height];
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
	batchNodes = new SpriteBatchNode*[1];
	batchNodes[0] = SpriteBatchNode::create(map->tileset->textures[0]);

	for (int i = 0; i < map->size.height; ++i)
	{
		sprites[i] = new Sprite*[(int)map->size.width];
		for (int j = 0; j < map->size.width; ++j)
		{
			sprites[i][j] = Sprite::create(map->tileset->textures[(int)map->tiles[i][j]]);
			batchNodes[0]->addChild(sprites[i][j],i*j);
		}
	}
}

MapInfo::~MapInfo()
{

}
