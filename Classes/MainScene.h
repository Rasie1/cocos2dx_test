#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"


class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    MainLayer * level;
	Creature * c;

    void update(float delayTime);
    void updateInfo(float delayTime);

    void menuCloseCallback(cocos2d::Ref* pSender);
    void keyboardPressCallback(EventKeyboard::KeyCode keyCode, Event * event);
    void mouseDownCallback(Event * event);
	bool touchBeganCallback(Touch * touch, Event * event);
    CREATE_FUNC(MainScene);

    Vec2 delta;
    Size visibleSize;
    Vec2 origin, center;
};





#endif
