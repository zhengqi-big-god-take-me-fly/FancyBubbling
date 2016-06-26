
#ifndef __OBJECTS_LAYER_H__
#define __OBJECTS_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class ObjectsLayer : public Layer {
public:
	static Scene * createScene();
	CREATE_FUNC(ObjectsLayer);
	virtual bool init();
	int getPlayerId(Node * node);
	Vec2 getGridPosition(Node * node);
	Vec2 getPlayerGridPosition(int p);
	void removeNode(Node * node);
	void useMap(const char * filename);
	void addPlayer(int index, int x, int y, const char * filename);
	void setAvatar(int p, const char * filename);
	void setHP(int p, int hp, int maxHp);
	void setPropsCount(int p, int i, int c);
	void setPlayerVelocity(int p, Vec2 v);
	void notifyReady(const char * text, float time = 1);

private:
	Sprite *backgroundImage;

	//Sprite *player1;
	//Sprite *player2;

	Vec2 player1_pos;
	Vec2 player2_pos;


	TMXTiledMap *map;

	Sprite *bubble1;
	Sprite *bubble2;

	Vec2 layerAnchor;
	Vec2 backgroundPos;
	Vec2 origin;
	Size layerSize;

	Vector<Node *> players;
	Vector<Node *> avatars;
	Vector<SpriteFrame*> p1_left;
	Vector<SpriteFrame*> p2_left;
	Vector<SpriteFrame*> p1_right;
	Vector<SpriteFrame*> p2_right;



};

#endif // !__OBJECTS_LAYER_H__
