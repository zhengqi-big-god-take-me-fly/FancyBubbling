#include "HomeScene.h"

Scene * HomeScene::createScene() {
	auto scene = Scene::create();
	auto layer = HomeScene::create();
	scene->addChild(layer);
	return scene;
}

bool HomeScene::init() {
	if (!Layer::init()) {
		return false;
	}

	// PresentLayer
	// Contains background, game title, and so on.
	auto presentLayer = Layer::create();
	addChild(presentLayer, 0);
	auto background = Sprite::create("home-background.png");
	presentLayer->addChild(background);

	// MenuLayer
	auto menuLayer = Menu::create();
	addChild(menuLayer, 1);

	return true;
}
