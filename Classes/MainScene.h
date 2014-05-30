#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"


class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    Terrain * terrain;

    void update(float delayTime);
    void updateInfo(float delayTime);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(MainScene);

    Vec2 delta;
    Size visibleSize;
    Vec2 origin, center;
};

#endif
