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
	auto m = new MapInfo(Size(90,90));
	terrain = Terrain::create(m);
	this->addChild(terrain, 7);
	delta = Vec2(0, 0);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW :
		{
			delta = Vec2(0, -3);
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		{
			delta = Vec2(0, 3);
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			delta = Vec2(-3, 0);
			break;
		}
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			delta = Vec2(3, 0);
			break;
		}
		case EventKeyboard::KeyCode::KEY_1:
		{
			delta = Vec2(0, 0);
			break;
		}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(MainScene::update));
	this->schedule(schedule_selector(MainScene::updateInfo), 0.1f);
	return true;
}

void MainScene::update(float delayTime)
{
	terrain->scroll(delta);
}

void MainScene::updateInfo(float delayTime)
{
	terrain->update();
}

void MainScene::menuCloseCallback(Ref* pSender)
{

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
