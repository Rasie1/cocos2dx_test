#include "MainScene.h"
#include "GameLayer.h"
#include "actor.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	center = Vec2(visibleSize.width/2, visibleSize.height / 2);

	auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	closeItem->setPosition(
			Vec2(
					origin.x + visibleSize.width
							- closeItem->getContentSize().width / 2,
					origin.y + closeItem->getContentSize().height / 2));


	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 999);
	auto m = new MapInfo(Size(150,150));
	level = MainLayer::create(m);
	this->addChild(level, 7);
	delta = Vec2(0, 0);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::keyboardPressCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	//auto mouseListener = EventListenerMouse::create();
	//mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::mouseDownCallback, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::touchBeganCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	c = Creature::create(m->playerStart, level);
	level->addChild(c, 999);
	level->setPosition(center);


	this->schedule(schedule_selector(MainScene::update));
	this->schedule(schedule_selector(MainScene::updateInfo), 0.5f);
	//this->terrain->setVisible(false);
	return true;
}


void MainScene::update(float delayTime)
{
	//level->scroll(delta);
	c->act();
}

void MainScene::updateInfo(float delayTime)
{
	level->update();
}

bool MainScene::touchBeganCallback(Touch * touch, Event * event)
{
	delta = Vec2(0, 0);
	this->c->MoveTo(level->convertToNodeSpace(touch->getLocation()));

	return true;
}


void MainScene::mouseDownCallback(Event * event)
{
	//delta = Vec2(0,0);
	//EventMouse * click = (EventMouse *)event;
	//this->c->MoveTo(Vec2(click->getCursorX(), click->getCursorY()));
}

void MainScene::menuCloseCallback(Ref* pSender)
{

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void MainScene::keyboardPressCallback(EventKeyboard::KeyCode keyCode, Event * event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW :
		{
			delta += Vec2(0, -3);
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		{
			delta += Vec2(0, 3);
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			delta += Vec2(-3, 0);
			break;
		}
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			delta += Vec2(3, 0);
			break;
		}
		case EventKeyboard::KeyCode::KEY_1:
		{
			delta = Vec2(0, 0);
			break;
		}
		default:
			break;
		}
}

