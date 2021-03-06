#include "ObjectsLayer.h"
#include <string>
#include "../Utils/Utils.h"

void ObjectsLayer::setPhysicsWorld(PhysicsWorld* world) { myWorld = world; }

//Scene * ObjectsLayer::createScene() {
//	auto scene = Scene::createWithPhysics();
//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
//	scene->getPhysicsWorld()->setGravity(Point(0, 0));
//
//	auto layer = ObjectsLayer::create(scene->getPhysicsWorld());
//	scene->addChild(layer);
//	return scene;
//}

bool ObjectsLayer::init(PhysicsWorld* world, GameSceneControllerDelegate * _controller) {
	if (!Layer::init()) {
		return false;
	}

	origin = Director::getInstance()->getVisibleOrigin();
	layerSize = Director::getInstance()->getVisibleSize();

	this->setPhysicsWorld(world);
    controller = _controller;

	addEdge();

	//player1->setPhysicsBody(PhysicsBody::createCircle(player1->getContentSize().height / 2));
	//player1->setAnchorPoint(Vec2(0.5, 0.5));
	//player1->setScale(0.5, 0.5);
	//player1->setPosition(player1_pos);

	//player2->setPhysicsBody(PhysicsBody::createCircle(player2->getContentSize().height / 2));
	//player2->setAnchorPoint(Vec2(0.5, 0.5));
	//player2->setScale(0.5, 0.5);
	//player2->setPosition(player2_pos);


	//Size t = backgroundImage->getContentSize();
	//backgroundImage->setScale((layerSize.width / t.width) * (layerSize.height / t.height));
	//backgroundImage->setPosition(origin.x + layerSize.width / 2, origin.y + layerSize.height / 2);

	//addChild(backgroundImage);

	//playerCount = 0;

    //Sprite * hpbar = Sprite::create("hp-foreground.png");
    //hps.pushBack(hpbar);
    //ProgressTimer * timer = ProgressTimer::create(hpbar);
    //timer->setAnchorPoint(Vec2(0.5f, 0));
    //timer->setPosition(origin.x + 36, origin.y + 56 + 108);
    //addChild(timer);
    //hpTimers.pushBack(timer);

    //hpbar = Sprite::create("hp-foreground.png");
    //hps.pushBack(hpbar);
    //timer = ProgressTimer::create(hpbar);
    //timer->setAnchorPoint(Vec2(0.5f, 0));
    //timer->setPosition(origin.x + layerSize.width - 36, origin.y + 56 + 108);
    //addChild(timer);
    //hpTimers.pushBack(timer);

	return true;
}

int ObjectsLayer::getPlayerId(Node * node)
{
    for (std::map<int, Node *>::iterator it = players.begin(); it != players.end(); ++it)
        if (it->second == node)
            return it->first;
    return -1;
	//int r = 0;
	//for (int i = 0; i < players.size(); i++) {
	//	if (players.at(i) == node) {
	//		r = i;
	//		break;
	//	}
	//}
	//return r;
}



ObjectsLayer * ObjectsLayer::create(PhysicsWorld * world, GameSceneControllerDelegate * _controller) {
	ObjectsLayer* pRet = new(std::nothrow) ObjectsLayer();
	if (pRet && pRet->init(world, _controller)) {
		pRet->autorelease();
		return pRet;
	}
	delete pRet;
	pRet = NULL;
	return NULL;
}

Vec2 ObjectsLayer::getGridPosition(Node * node)
{
    if (node == nullptr) return InvalidGridPosition;
    return Vec2(((int)node->getPositionX()) / 40, 12 - ((int)node->getPositionY()) / 40);
	//int x, y;
	//Vec2 worldPos = convertToWorldSpace(node->getPosition());
	//x = (worldPos.x - 180) / 40;
	//int modx = int(worldPos.x - 180) % 40;
	//y = (worldPos.y - 60) / 40;
	//int mody = int(worldPos.y - 60) % 40;
	//
	//if (modx == 0) x += 1;
	//if (mody == 0) y += 1;

	//if (x >= 14) x = 14;
	//if (y >= 12) y = 12;
	//if (x <= 0) x = 0;
	//if (y <= 0) y = 0;

	//return Vec2(15 - 1 - x , 13 - 1 - y);
}

Vec2 ObjectsLayer::getPlayerGridPosition(int p)
{
    auto player = players.find(p);
    if (player != players.end())
        return getGridPosition(player->second);
	return InvalidGridPosition;
}

void ObjectsLayer::removeNode(Node * node)
{
	if (node == nullptr) return;
    node->removeFromParent();
}

void ObjectsLayer::useMap(const char * filename)
{
	map = TMXTiledMap::create(filename);
    map->setAnchorPoint(Vec2(0.5f, 1));
	Vec2 acturalPos = Vec2(origin.x + layerSize.width / 2, origin.y + layerSize.height - 40);
	map->setPosition(acturalPos);
	this->addChild(map, 0);
}

void ObjectsLayer::addPlayer(int index, int x, int y, const char * filename)
{

    // Add resource to cache
    auto sfc = SpriteFrameCache::getInstance();
    if (sfc->isSpriteFramesWithFileLoaded(std::string(filename) + ".plist") == false) {
        sfc->addSpriteFramesWithFile(std::string(filename) + ".plist");
        Utils::loadAnimation(std::string(filename) + "-up", std::string(filename) + "-up" + "-%d.png", 0, 3, 1.0f / 10);
        Utils::loadAnimation(std::string(filename) + "-down", std::string(filename) + "-down" + "-%d.png", 0, 3, 1.0f / 10);
        Utils::loadAnimation(std::string(filename) + "-left", std::string(filename) + "-left" + "-%d.png", 0, 3, 1.0f / 10);
        Utils::loadAnimation(std::string(filename) + "-right", std::string(filename) + "-right" + "-%d.png", 0, 3, 1.0f / 10);
    }

    // Create sprite
    char frameName[128];
    sprintf(frameName, "%s-%s-%d.png", filename, "down", 0);
    auto player = Sprite::createWithSpriteFrameName(frameName);
    setGridPosition(player, x, y);
    //player->setPhysicsBody(PhysicsBody::createCircle(20));
    map->addChild(player);
    players.insert(std::make_pair(index, player));
}
//
//void ObjectsLayer::setHP(int p, int hp, int maxHp)
//{
//	if (p < 0 || p > 2 || p > hps.size()) return;
//	(hpTimers.at(p))->setPercentage(float(hp)/maxHp);
//}

void ObjectsLayer::setPlayerVelocity(int p, Vec2 v)
{
    players.at(p)->getPhysicsBody()->setVelocity(v);
}

void ObjectsLayer::notifyReady(const char * text, float time)
{
	auto notifyText = Label::createWithTTF(text, "fonts/theme-font.ttf", 64, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	notifyText->setPosition(layerSize.width / 2, layerSize.height / 2);
    notifyText->runAction(Sequence::createWithTwoActions(ScaleTo::create(time, 1), CallFuncN::create([](Node * node) {
        node->removeFromParent();
    })));
    addChild(notifyText, 4);
}

void ObjectsLayer::setGridPosition(Node *dest , int x , int y)
{
	if (x < 0 || x > 15 || y < 0 || y > 13) return;
	
	Vec2 absolutePosition = Vec2(x * 40 + 20 , (13 - y - 1) * 40 + 20);
	Vec2 thisLayerPosition = convertToNodeSpace(absolutePosition);
	dest->setPosition(thisLayerPosition);
}

void ObjectsLayer::addEdge(void)
{
	//auto bound = PhysicsBody::createEdgeBox(Size(600, 520));
	//bound->setDynamic(false);
	//bound->setTag(0);

	edge = Sprite::create();
	edge->setPosition(Point(layerSize.width / 2 , 340));
	//edge->setPhysicsBody(bound);
	addChild(edge);
}

void ObjectsLayer::configTilePhysics(int x, int y, PhysicsBody * body) {
    auto sprite = getTile(x, y);
    sprite->setPhysicsBody(body);
}

void ObjectsLayer::configPlayerPhysics(int p, PhysicsBody * body) {
    players.at(p)->setPhysicsBody(body);
}

void ObjectsLayer::configEdgePhysics(PhysicsBody * body) {
    edge->setPhysicsBody(body);
}

void ObjectsLayer::updatePlayerZ() {
    for (std::map<int, Node *>::iterator it = players.begin(); it != players.end(); ++it) {
        it->second->setLocalZOrder(getZOrderOfRow(getPlayerGridPosition(it->first).y));
    }
}

void ObjectsLayer::playMovingAnimation(int p, int d) {
    std::string direction = "default";
    //char frameName[128];
    
    switch (d) {
        case 0:
            direction = "up";
            break;
        case 1:
            direction = "down";
            break;
        case 2:
            direction = "left";
            break;
        case 3:
            direction = "right";
            break;
        default:
            break;
    }

    //Vector<SpriteFrame *> caches;
    //for (int i = 0; i < 4; i++) {
    //    sprintf(frameName, "player-%d-%s-%d.png", p, direction.c_str(), i);
    //    SpriteFrame* time = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
    //    caches.pushBack(time);
    //}

    char aniName[128];
    //sprintf(aniName, "player-%d", p);
    //auto sfc = SpriteFrameCache::getInstance();
    //if (sfc->isSpriteFramesWithFileLoaded(std::string(aniName) + ".plist") == false) {
    //    sfc->addSpriteFramesWithFile(std::string(aniName) + ".plist");
    //    Utils::loadAnimation(std::string(aniName) + "-up"   , std::string(aniName) + "-up" + "-%d.png", 0, 3, 1.0f / 10);
    //    Utils::loadAnimation(std::string(aniName) + "-down" , std::string(aniName) + "-down" + "-%d.png", 0, 3, 1.0f / 10);
    //    Utils::loadAnimation(std::string(aniName) + "-left" , std::string(aniName) + "-left" + "-%d.png", 0, 3, 1.0f / 10);
    //    Utils::loadAnimation(std::string(aniName) + "-right", std::string(aniName) + "-right" + "-%d.png", 0, 3, 1.0f / 10);
    //}
    sprintf(aniName, "player-%d-%s", p, direction.c_str());
    Animation *anim = AnimationCache::getInstance()->getAnimation(aniName);
    auto rp = RepeatForever::create(Animate::create(anim));
    rp->setTag(999);
    players.at(p)->runAction(rp);


}

void ObjectsLayer::stopMovingAnimation(int p) {
    players.at(p)->stopActionByTag(999);
}

void ObjectsLayer::playHurtAnimation(int p) {
    players.at(p)->runAction(Repeat::create(Sequence::createWithTwoActions(TintBy::create(0.15f, 255, 0, 0), TintBy::create(0.15f, 0, 0, 0)), 3));
}

void ObjectsLayer::playerDie(int p) {
    auto shade = TintBy::create(0.5 , -50, -50, -50);
    players.at(p)->runAction(Repeat::create(shade, 1));
}

void ObjectsLayer::playerProtected(int p, bool protect) {
    // add the file into the animation list;
 /*   std::string protection = "";
    char frameName[128];
    Vector<SpriteFrame *> caches;
    for (int i = 0; i < 4; i++) {
        sprintf(frameName, "%s-%d.png" , protection.c_str() , i);
        SpriteFrame* time = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        caches.pushBack(time);
    }
*/
	if (!protect) players.at(p)->removeChildByTag(11111);
	else {
        auto effect = Sprite::createWithSpriteFrameName("protected-0.png");
        effect->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("protected"))));
        effect->setPosition(players.at(p)->getContentSize().width / 2, players.at(p)->getContentSize().height / 2);
        effect->setTag(11111);
        players.at(p)->addChild(effect);
	}

}

// show and live is deprecated
void ObjectsLayer::addWave(Vec2 start, Vec2 end, float show, float live, const std::string & filename, PhysicsBody * body) {
    auto result = end - start;
    result.y = -result.y;
    //if (result == Vec2::ZERO) return;
    auto wave = Sprite::create(filename);
    map->addChild(wave, 20);
    setGridPosition(wave, start.x, start.y);
    wave->setPhysicsBody(body);
    wave->getPhysicsBody()->setVelocity(result / result.getLength() * 400);
    wave->runAction(Sequence::createWithTwoActions(ScaleTo::create(result == Vec2::ZERO ? 0.1f / 60 : ((0.1f * result.getLength()) - 1.0f / 60), 1), CallFuncN::create([this](Node * node) {
        this->disposeWave(node);
    })));
}

int ObjectsLayer::getZOrderOfRow(int y) {
    char layerName[128];
    sprintf(layerName, "Row%d", y);
    return map->getLayer(layerName)->getLocalZOrder();
}

void ObjectsLayer::removeTile(int x, int y) {
    char layerName[128];
    sprintf(layerName, "Row%d", y);
    auto layer = map->getLayer(layerName);
    layer->getTileAt(Vec2(x, y))->removeFromParent();
    if (y > 0 && layer->getTileAt(Vec2(x, y - 1)) != nullptr) layer->getTileAt(Vec2(x, y - 1))->removeFromParent();
}

void ObjectsLayer::placeBubble(int x, int y, PhysicsBody * body, float time) {
    auto sfc = SpriteFrameCache::getInstance();
    if (sfc->isSpriteFramesWithFileLoaded("bubble.plist") == false) {
        sfc->addSpriteFramesWithFile("bubble.plist");
        Utils::loadAnimation("bubble", "bubble-%d.png", 0, 3, 1.0f / 10);
    }
    Sprite * bubble = Sprite::createWithSpriteFrameName("bubble-0.png");
    setGridPosition(bubble, x, y);
    bubble->setPhysicsBody(body);
    bubble->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("bubble"))));
    bubble->scheduleOnce([bubble, this](float delta) {
        this->controller->bubbleExplode(bubble);
    }, time, "bubble");
    map->addChild(bubble, getZOrderOfRow(y));
}

void ObjectsLayer::addProps(int x, int y, const std::string & filename, PhysicsBody * body) {
    auto props = Sprite::create(filename);
    props->setPhysicsBody(body);
    setGridPosition(props, x, y);
    map->addChild(props);
}

void ObjectsLayer::disposeWave(Node * wave) {
    wave->removeFromParent();
}

Node * ObjectsLayer::getTile(int x, int y) {
    char layerName[128];
    sprintf(layerName, "Row%d", y);
    return map->getLayer(layerName)->getTileAt(Vec2(x, y));
}
