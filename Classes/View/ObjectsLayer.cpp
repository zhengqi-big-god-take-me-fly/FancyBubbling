#include "ObjectsLayer.h"

Scene * ObjectsLayer::createScene() {
	auto scene = Scene::create();
	auto layer = ObjectsLayer::create();
	scene->addChild(layer);
	return scene;
}

bool ObjectsLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	origin = Director::getInstance()->getVisibleOrigin();
	layerSize = Director::getInstance()->getVisibleSize();

	// Playing Background
	backgroundImage = Sprite::create("game-area-background.png");

	//player1->setPhysicsBody(PhysicsBody::createCircle(player1->getContentSize().height / 2));
	//player1->setAnchorPoint(Vec2(0.5, 0.5));
	//player1->setScale(0.5, 0.5);
	//player1->setPosition(player1_pos);

	//player2->setPhysicsBody(PhysicsBody::createCircle(player2->getContentSize().height / 2));
	//player2->setAnchorPoint(Vec2(0.5, 0.5));
	//player2->setScale(0.5, 0.5);
	//player2->setPosition(player2_pos);


	Size t = backgroundImage->getContentSize();
	backgroundImage->setScale((layerSize.width / t.width) * (layerSize.height / t.height));
	backgroundImage->setPosition(origin.x + layerSize.width / 2, origin.y + layerSize.height / 2);

	addChild(backgroundImage);

	return true;
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif

