#include "GameSceneView.h"

GameSceneView * GameSceneView::create(GameSceneControllerDelegate * _controller, PhysicsWorld * _world) {
    GameSceneView *pRet = new(std::nothrow) GameSceneView();
    if (pRet && pRet->init(_controller, _world)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool GameSceneView::init(GameSceneControllerDelegate * _controller, PhysicsWorld * _world) {
    if (_controller == nullptr) return false;

    vo = Director::getInstance()->getVisibleOrigin();
    vs = Director::getInstance()->getVisibleSize();

    controller = _controller;

    backgroundLayer = BackgroundLayer::create();
    addChild(backgroundLayer, 0);
    objectsLayer = ObjectsLayer::create(_world);
    addChild(objectsLayer, 1);
    hudLayer = HudLayer::create();
    addChild(hudLayer, 2);

    return true;
}
