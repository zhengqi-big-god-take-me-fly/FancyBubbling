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

int GameSceneView::getPlayerId(Node * node) {
    return objectsLayer->getPlayerId(node);
}

Vec2 GameSceneView::getGridPosition(Node * node) {
    return objectsLayer->getGridPosition(node);
}

Vec2 GameSceneView::getPlayerGridPosition(int p) {
    return objectsLayer->getPlayerGridPosition(p);
}

void GameSceneView::removeNode(Node * node) {
    objectsLayer->removeNode(node);
}

void GameSceneView::useMap(const char * filename) {
    objectsLayer->useMap(filename);
}

void GameSceneView::addPlayer(int index, int x, int y, const char * filename) {
    objectsLayer->addPlayer(index, x, y, filename);
}

void GameSceneView::setHP(int p, int hp, int maxHp) {
    objectsLayer->setHP(p, hp, maxHp);
}

void GameSceneView::setPropsCount(int p, int i, int c) {
    objectsLayer->setPropsCount(p, i, c);
}

void GameSceneView::setPlayerVelocity(int p, Vec2 v) {
    objectsLayer->setPlayerVelocity(p, v);
}

void GameSceneView::notifyReady(const char * text, float time) {
    objectsLayer->notifyReady(text, time);
}

void GameSceneView::showPauseScreen() {
    auto vo = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    pauseScreen = Sprite::create("pause-screen.png");
    pauseScreen->setPosition(vo.x + vs.width / 2, vo.y + vs.height / 2);
    addChild(pauseScreen, 5);
}

void GameSceneView::hidePauseScreen() {
    if (pauseScreen != nullptr) {
        pauseScreen->removeFromParent();
        pauseScreen = nullptr;
    }
}

void GameSceneView::configPhysics(int x, int y, PhysicsBody * body) {
    objectsLayer->configPhysics(x, y, body);
}

void GameSceneView::configEdgePhysics(PhysicsBody * body) {
    objectsLayer->configEdgePhysics(body);
}
