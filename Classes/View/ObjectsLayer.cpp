#include "ObjectsLayer.h"
#include <string>

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

bool ObjectsLayer::init(PhysicsWorld* world) {
	if (!Layer::init()) {
		return false;
	}

	origin = Director::getInstance()->getVisibleOrigin();
	layerSize = Director::getInstance()->getVisibleSize();

	this->setPhysicsWorld(world);

	addEdge();

	//for (int i = 0; i < 2; i++) {
	//	//players.pushBack(NULL);
	//	//hps.pushBack(NULL);
	//	//avatars.pushBack(NULL);
	//	//hpTimers.pushBack(NULL);
	//}

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

ObjectsLayer * ObjectsLayer::create(PhysicsWorld * world) {
	ObjectsLayer* pRet = new(std::nothrow) ObjectsLayer();
	if (pRet && pRet->init(world)) {
		pRet->autorelease();
		return pRet;
	}
	delete pRet;
	pRet = NULL;
	return NULL;
}

Vec2 ObjectsLayer::getGridPosition(Node * node)
{
    if (node == NULL) return Vec2(-1, -1);
	int x, y;
	Vec2 worldPos = convertToWorldSpace(node->getPosition());
	x = (worldPos.x - 180) / 40;
	int modx = int(worldPos.x - 180) % 40;
	y = (worldPos.y - 60) / 40;
	int mody = int(worldPos.y - 60) % 40;
	
	if (modx == 0) x += 1;
	if (mody == 0) y += 1;

	if (x >= 14) x = 14;
	if (y >= 12) y = 12;
	if (x <= 0) x = 0;
	if (y <= 0) y = 0;

	return Vec2(15 - 1 - x , 13 - 1 - y);
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
	//char *con;
	//itoa(index, con, 10);
    //
	//if (playerCount >= 2 || index < 0 || index > 2 || index > players.size()) return;
	//if (index == 1) {
	//	auto texture = Director::getInstance()->getTextureCache()->addImage("player-1.png");
	//	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 40, 64)));
	//	players.replace(1, Sprite::createWithSpriteFrame(frame0));
	//	setGridPosition(players.at(1), x, y);
	//	players.at(1)->setPhysicsBody(PhysicsBody::createCircle(32));
	//	p2_left.reserve(6);
	//	for (int i = 3; i < 9; i++) {
	//		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(40 * (i % 4) , 64 * (i / 4), 40, 64)));
	//		p2_left.pushBack(frame);
	//	}
    //
	//	p2_right.reserve(6);
	//	for (int i = 11; i < 16; i++) {
	//		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(40 * (i % 4), 64 * (i / 4), 40, 64)));
	//		p2_right.pushBack(frame);
	//	}
	//	playerCount++;
	//}
	//else {
	//	auto texture2 = Director::getInstance()->getTextureCache()->addImage("res/player-0.png");
	//	auto frame1 = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 40, 64)));
	//	players.replace(0, Sprite::createWithSpriteFrame(frame1));
	//	setGridPosition(players.at(0), x, y);
	//	players.at(0)->setPhysicsBody(PhysicsBody::createCircle(32));
	//	p1_left.reserve(6);
	//	for (int i = 3; i < 9; i++) {
	//		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(40 * (i % 4), 64 * (i / 4), 40, 64)));
	//		p1_left.pushBack(frame);
	//	}
    //
	//	p1_right.reserve(6);
	//	for (int i = 11; i < 16; i++) {
	//		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(40 * (i % 4), 64 * (i / 4), 40, 64)));
	//		p1_right.pushBack(frame);
	//	}
	//	playerCount++;
	//}

    // Add resource to cache
    auto sfc = SpriteFrameCache::getInstance();
    if (sfc->isSpriteFramesWithFileLoaded(std::string(filename) + ".plist") == false) {
        sfc->addSpriteFramesWithFile(std::string(filename) + ".plist");
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

void ObjectsLayer::setHP(int p, int hp, int maxHp)
{
	if (p < 0 || p > 2 || p > hps.size()) return;
	if (hps.at(p) == NULL) {
		Sprite *myHP = Sprite::create("res/hp-foreground.png", CC_RECT_PIXELS_TO_POINTS(Rect(28, 56, 12, 454)));
		hps.replace(p, myHP);
		hpTimers.replace(p, ProgressTimer::create(myHP));
		(hpTimers.at(p))->setScaleX(90);
		(hpTimers.at(p))->setAnchorPoint(Vec2(0, 0));
		(hpTimers.at(p))->setType(ProgressTimerType::BAR);
		(hpTimers.at(p))->setBarChangeRate(Point(1, 0));
		(hpTimers.at(p))->setMidpoint(Point(0, 1));
		(hpTimers.at(p))->setPosition(convertToNodeSpace(Vec2(28, 56)));
	}
	(hpTimers.at(p))->setPercentage(float(hp)/maxHp);
}

void ObjectsLayer::setPropsCount(int p, int i, int c)
{
	//Not implemented Yet
}

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
	if (x < 0 || x > 14 || y < 0 || y > 13) return;
	
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
    char layerName[128];
    for (std::map<int, Node *>::iterator it = players.begin(); it != players.end(); ++it) {
        sprintf(layerName, "Row%d", (int)getPlayerGridPosition(it->first).y);
        it->second->setLocalZOrder(map->getLayer(layerName)->getLocalZOrder());
    }
}

Node * ObjectsLayer::getTile(int x, int y) {
    char layerName[128];
    sprintf(layerName, "Row%d", y);
    return map->getLayer(layerName)->getTileAt(Vec2(x, y));
}
