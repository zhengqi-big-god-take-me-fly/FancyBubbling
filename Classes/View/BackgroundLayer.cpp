#include "BackgroundLayer.h"

Scene * BackgroundLayer::createScene() {
	auto scene = Scene::create();
	auto layer = BackgroundLayer::create();
	scene->addChild(layer);
	return scene;
}

bool BackgroundLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	origin = Director::getInstance()->getVisibleOrigin();
	layerSize = Director::getInstance()->getVisibleSize();

	backgroundImage = Sprite::create("game-area-background.png");
	Size t = backgroundImage->getContentSize();
	backgroundImage->setScale((layerSize.width / t.width) * (layerSize.height / t.height));
	backgroundImage->setPosition(origin.x + layerSize.width / 2, origin.y + layerSize.height / 2);
	
	addChild(backgroundImage);

	return true;
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

