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
    startGameButton->setAnchorPoint(Vec2(0, 0.5));
    startGameButton->setPosition(vo.x + 64, vo.y + 240);
    auto helpGameButton = MenuItemImage::create("help-game-normal.png", "help-game-pressed.png", CC_CALLBACK_1(HomeScene::onHelpGameClick, this));
    helpGameButton->setAnchorPoint(Vec2(0, 0.5));
    helpGameButton->setPosition(vo.x + 64, vo.y + 160);
	auto aboutGameButton = MenuItemImage::create("about-game-normal.png", "about-game-pressed.png", CC_CALLBACK_1(HomeScene::onAboutGameClick, this));
    aboutGameButton->setAnchorPoint(Vec2(1, 0.5));
    aboutGameButton->setPosition(vo.x + vs.width - 64, vo.y + 240);
	auto exitGameButton = MenuItemImage::create("exit-game-normal.png", "exit-game-pressed.png", CC_CALLBACK_1(HomeScene::onExitGameClick, this));
    exitGameButton->setAnchorPoint(Vec2(1, 0.5));
    exitGameButton->setPosition(vo.x + vs.width - 64, vo.y + 160);
	auto menuLayer = Menu::create(startGameButton, helpGameButton, aboutGameButton, exitGameButton, nullptr);
    menuLayer->setPosition(vo.x, vo.y);
	addChild(menuLayer, 1);

	return true;
}

void HomeScene::onStartGameClick(Ref * sender) {
    auto scene = GameSceneController::createScene();
    Director::getInstance()->pushScene(scene);
}

void HomeScene::onHelpGameClick(Ref * sender) {
    popupScreen = Sprite::create("game-help.png");
    popupScreen->setPosition(vo.x + vs.width / 2, vo.y + vs.height / 2);
    popupScreen->runAction(FadeIn::create(0.4f));
    addChild(popupScreen, 5);
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HomeScene::onPopupScreenTouchBegan, this);
    touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, popupScreen);
}

void HomeScene::onAboutGameClick(Ref * sender) {
    popupScreen = Sprite::create("game-about.png");
    popupScreen->setPosition(vo.x + vs.width / 2, vo.y + vs.height / 2);
    popupScreen->runAction(FadeIn::create(0.4f));
    addChild(popupScreen, 5);
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HomeScene::onPopupScreenTouchBegan, this);
    touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, popupScreen);
}

void HomeScene::onExitGameClick(Ref * sender) {
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

bool HomeScene::onPopupScreenTouchBegan(Touch * touch, Event * e) {
    if (popupScreen != nullptr && popupScreen->getOpacity() == 255) {
        popupScreen->runAction(Sequence::createWithTwoActions(FadeOut::create(0.4f), CallFuncN::create([this](Node * node) {
            node->removeFromParent();
            this->popupScreen = nullptr;
        })));
        return true;
    }
    return false;
}
