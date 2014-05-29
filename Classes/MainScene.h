#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"
/*
class GameSprite : public Sprite
{
public:
	Vec2 vector;
	Touch * touch;
	Vec2 nextPosition;
	//Size size;

	GameSprite();
	~GameSprite();

	static GameSprite * gameSpriteWithFile(const char * fileName);
	virtual void setPosition(const Vec2& pos);

};*/


class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    Terrain * terrain;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
};

#endif
