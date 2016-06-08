#include "HomeScene.h"
#include "../GameScene/GameSceneController.h"

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

	vo = Director::getInstance()->getVisibleOrigin();
	vs = Director::getInstance()->getVisibleSize();

	// PresentLayer
	// Contains background, game title, and so on.
	auto presentLayer = Layer::create();
	addChild(presentLayer, 0);
	auto background = Sprite::create("home-background.png");
    background->setPosition(vo.x + vs.width / 2, vo.y + vs.height / 2);
	presentLayer->addChild(background);

	// MenuLayer
	auto startGameButton = MenuItemImage::create("start-game-normal.png", "start-game-pressed.png", CC_CALLBACK_1(HomeScene::onStartGameClick , this));
    startGameButton->setPosition(vo.x, vo.y);
	auto aboutGameButton = MenuItemImage::create("about-game-normal.png", "about-game-pressed.png", CC_CALLBACK_1(HomeScene::onAboutGameClick, this));
    aboutGameButton->setPosition(vo.x + vs.width / 2, vo.y + vs.height / 2);
	auto exitGameButton = MenuItemImage::create("exit-game-normal.png", "exit-game-pressed.png", CC_CALLBACK_1(HomeScene::onExitGameClick, this));
    exitGameButton->setPosition(vo.x + vs.width, vo.y);
	auto menuLayer = Menu::create(startGameButton, aboutGameButton, exitGameButton, nullptr);
    menuLayer->setPosition(vo.x, vo.y);
	addChild(menuLayer, 1);

	return true;
}

void HomeScene::onStartGameClick(Ref * sender) {
    auto scene = GameSceneController::createScene();
    Director::getInstance()->pushScene(scene);
}

void HomeScene::onAboutGameClick(Ref * sender) {}

void HomeScene::onExitGameClick(Ref * sender) {
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
