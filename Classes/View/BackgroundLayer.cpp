#include "BackgroundLayer.h"
//
//Scene * BackgroundLayer::createScene() {
//	auto scene = Scene::create();
//	auto layer = BackgroundLayer::create();
//	scene->addChild(layer);
//	return scene;
//}

void BackgroundLayer::winGame(int p) {
	auto winScene = Sprite::create("winner.png");
	winScene->setAnchorPoint(Vec2(0, 0));
	winScene->setPosition(origin.x, origin.y);

	std::string s = (p == 0 ? "avatar-0.png" : "avatar-1.png");
	auto winPlayer = Sprite::create(s);
	winPlayer->setAnchorPoint(Vec2(0, 0));
	winPlayer->setPosition(origin.x + layerSize.width / 2, origin.y + 182);
	addChild(winScene, 1);
	addChild(winPlayer, 2);
}

bool BackgroundLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	origin = Director::getInstance()->getVisibleOrigin();
	layerSize = Director::getInstance()->getVisibleSize();

	backgroundImage = Sprite::create("game-ui-background.png");
	Size t = backgroundImage->getContentSize();
	//backgroundImage->setScale((layerSize.width / t.width) * (layerSize.height / t.height));
	backgroundImage->setPosition(origin.x + layerSize.width / 2, origin.y + layerSize.height / 2);
	
	uiBackground = Sprite::create("game-area-border.png");
	Size uiSize = uiBackground->getContentSize();
	//uiBackground->setScaleX((layerSize.width / uiSize.width) * 0.7);
	//uiBackground->setScaleY((layerSize.height / uiSize.height) * 0.8);
	//uiBackground->setContentSize(Size(600, 520));
    uiBackground->setAnchorPoint(Vec2(0.5f, 0));
	uiBackground->setPosition(origin.x + layerSize.width / 2, origin.y + 56);

	addChild(backgroundImage);
	addChild(uiBackground);
	return true;
}
