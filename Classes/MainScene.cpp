#include "MainScene.h"
#include "GameLayer.h"

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
	auto m = new MapInfo(Size(1000,1000));
	level = MainLayer::create(m);
	this->addChild(level, 7);
	delta = Vec2(0, 0);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::keyboardPressCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::mouseDownCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);




	auto p = Creature::create(Vec2(3,4));
	this->addChild(p, 9999);



	this->schedule(schedule_selector(MainScene::update));
	this->schedule(schedule_selector(MainScene::updateInfo), 0.1f);
	//this->terrain->setVisible(false);
	return true;
}


void MainScene::update(float delayTime)
{
	level->scroll(delta);
}

void MainScene::updateInfo(float delayTime)
{
	level->update();
}

void MainScene::mouseDownCallback(Event * event)
{
	delta = Vec2(0,0);
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

