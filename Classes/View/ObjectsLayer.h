
#ifndef __OBJECTS_LAYER_H__
#define __OBJECTS_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class ObjectsLayer : public Layer {
public:
	virtual bool init(PhysicsWorld * world);
	int getPlayerId(Node * node);
	static ObjectsLayer * create(PhysicsWorld * world);
	Vec2 getGridPosition(Node * node);
	Vec2 getPlayerGridPosition(int p);
	void removeNode(Node * node);
	void useMap(const char * filename);
	void addPlayer(int index, int x, int y, const char * filename);
	//void setAvatar(int p, const char * filename);
	void setHP(int p, int hp, int maxHp);
	void setPropsCount(int p, int i, int c);
	void setPlayerVelocity(int p, Vec2 v);
	void notifyReady(const char * text, float time = 1);
	void setGridPosition(Node *dest , int x, int y);
	//void deprecateLabel(float time);
	void setPhysicsWorld(PhysicsWorld* world);
	void addEdge(void);
    void configTilePhysics(int x, int y, PhysicsBody * body);
    void configPlayerPhysics(int p, PhysicsBody * body);
    void configEdgePhysics(PhysicsBody * body);
    void placeBubble(int x, int y);
    void addProps(int x, int y, const std::string & filename);
    void disposeWave(float dt);
    void updatePlayerZ();
    void playMovingAnimation(int p, int d);
    void stopMovingAnimation(int p);
    void playHurtAnimation(int p);
    void playerDie(int p);
    void playerProtected(int p, bool protect);
    void addWave(Vec2 start, Vec2 end, float show, float live, const std::string & filename, PhysicsBody * body);
private:
	int playerCount;
	Vec2 player1_pos;
	Vec2 player2_pos;
    
	PhysicsWorld *myWorld;
	Sprite *edge;

	TMXTiledMap *map;

	Vec2 layerAnchor;
	Vec2 backgroundPos;
	Vec2 origin;
	Size layerSize;

	//Vector<Node *> players;
    std::map<int, Node *> players;
	Vector<Node *> hps;
	Vector<ProgressTimer *> hpTimers;
	Vector<SpriteFrame*> p1_left;
	Vector<SpriteFrame*> p2_left;
	Vector<SpriteFrame*> p1_right;
	Vector<SpriteFrame*> p2_right;

	Label *notifyText;

    // Constancts
    Vec2 InvalidGridPosition = Vec2(-1, -1);

    Node * getTile(int x, int y);
};

#endif // !__OBJECTS_LAYER_H__

