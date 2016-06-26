#include "ObjectsLayer.h"
#include <string>
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

int ObjectsLayer::getPlayerId(Node * node)
{
	int r = 0;
	for (int i = 0; i < players.size; i++) {
		if (players.at(i) == node) {
			r = i;
			break;
		}
	}
	return r;
}

Vec2 ObjectsLayer::getGridPosition(Node * node)
{
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
	if (0 <= p && p < 2) {
		return ObjectsLayer::getGridPosition(ObjectsLayer::players.at(p));
	}
	return Vec2(0,0);
}

void ObjectsLayer::removeNode(Node * node)
{
	this->removeFromParentAndCleanup(node);
}

void ObjectsLayer::useMap(const char * filename)
{
	map = TMXTiledMap::create(filename);
	Vec2 acturalPos = Vec2(layerSize.width / 2 - 300, layerSize.height / 2 - 260);
	map->setPosition(acturalPos);
	this->addChild(map, 0);
}

void ObjectsLayer::addPlayer(int index, int x, int y, const char * filename)
{
	//char *con;
	//itoa(index, con, 10);

	if (index < 0 || index > 2 || index > players.size) return;

	if (index == 1) {
		auto texture = Director::getInstance()->getTextureCache()->addImage("player-1.png");
		auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 40, 64)));
		players.insert(1 ,Sprite::createWithSpriteFrame(frame0));

		p2_left.reserve(6);
		for (int i = 3; i < 9; i++) {
			auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(40 * (i % 4) , 64 * (i / 4), 40, 64)));
			p2_left.pushBack(frame);
		}

		p2_right.reserve(6);
		for (int i = 11; i < 16; i++) {
			auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(40 * (i % 4), 64 * (i / 4), 40, 64)));
			p2_right.pushBack(frame);
		}
	}
	else {
		auto texture2 = Director::getInstance()->getTextureCache()->addImage("player-0.png");
		auto frame1 = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 40, 64)));
		players.insert(0, Sprite::createWithSpriteFrame(frame1));

		p1_left.reserve(6);
		for (int i = 3; i < 9; i++) {
			auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(40 * (i % 4), 64 * (i / 4), 40, 64)));
			p1_left.pushBack(frame);
		}

		p1_right.reserve(6);
		for (int i = 11; i < 16; i++) {
			auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(40 * (i % 4), 64 * (i / 4), 40, 64)));
			p1_right.pushBack(frame);
		}
	}
}

void ObjectsLayer::setAvatar(int p, const char * filename)
{
	if (p < 0 || p > 2 || p > avatars.size) return;
	if (avatars.size > 2) return;
	avatars.insert(p, Sprite::create(filename));
}

void ObjectsLayer::setHP(int p, int hp, int maxHp)
{

}

void ObjectsLayer::setPropsCount(int p, int i, int c)
{

}

void ObjectsLayer::setPlayerVelocity(int p, Vec2 v)
{

}

void ObjectsLayer::notifyReady(const char * text, float time)
{

}







//Vec2 getPlayerGridPosition(int p) {
//	if (0 <= p && p < 2) {
//		return ObjectsLayer::getGridPosi)
//	}
//}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif

