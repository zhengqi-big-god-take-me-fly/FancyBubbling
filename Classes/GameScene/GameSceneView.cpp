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
    objectsLayer = ObjectsLayer::create(_world, controller);
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
    hudLayer->setHP(p, hp, maxHp);
}

void GameSceneView::setPropsCount(int p, int i, int c) {
    hudLayer->setPropsCount(p, i, c);
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

void GameSceneView::configTilePhysics(int x, int y, PhysicsBody * body) {
    objectsLayer->configTilePhysics(x, y, body);
}

void GameSceneView::configPlayerPhysics(int p, PhysicsBody * body) {
    objectsLayer->configPlayerPhysics(p, body);
}

void GameSceneView::configEdgePhysics(PhysicsBody * body) {
    objectsLayer->configEdgePhysics(body);
}

void GameSceneView::updatePlayerZ() {
    objectsLayer->updatePlayerZ();
}

void GameSceneView::placeBubble(int x, int y, PhysicsBody * body, float time) {
    objectsLayer->placeBubble(x, y, body, time);
}

void GameSceneView::addProps(int x, int y, const std::string & filename, PhysicsBody * body) {
    objectsLayer->addProps(x, y, filename, body);
}

void GameSceneView::playMovingAnimation(int p, int d) {
    objectsLayer->playMovingAnimation(p, d);
}

void GameSceneView::stopMovingAnimation(int p) {
    objectsLayer->stopMovingAnimation(p);
}

void GameSceneView::playHurtAnimation(int p) {
    objectsLayer->playHurtAnimation(p);
}

void GameSceneView::playerDie(int p) {
    objectsLayer->playerDie(p);
}

void GameSceneView::playerProtected(int p, bool protect) {
    objectsLayer->playerProtected(p, protect);
}

void GameSceneView::addWave(Vec2 start, Vec2 end, float show, float live, const std::string & filename, PhysicsBody * body) {
    objectsLayer->addWave(start, end, show, live, filename, body);
}

void GameSceneView::removeTile(int x, int y) {
    objectsLayer->removeTile(x, y);
}
