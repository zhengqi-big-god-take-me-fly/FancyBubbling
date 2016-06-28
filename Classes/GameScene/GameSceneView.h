#ifndef __GAME_SCENE_VIEW_H__
#define __GAME_SCENE_VIEW_H__

#include "cocos2d.h"
#include "GameSceneControllerDelegate.h"
#include "../View/BackgroundLayer.h"
#include "../View/HudLayer.h"
#include "../View/ObjectsLayer.h"
//#include "../View/BackgroundLayer.h"
//#include "../View/HudLayer.h"
//#include "../View/ObjectsLayer.h"
//
USING_NS_CC;

/*
Node to hold all Layers and prepare callbacks.
*/
class GameSceneView : public Node {
public:
    static GameSceneView * create(GameSceneControllerDelegate * _controller, PhysicsWorld * _world);
    virtual bool init(GameSceneControllerDelegate * _controller, PhysicsWorld * _world);
    // Public interface
    int getPlayerId(Node * node);
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
    //void setGridPosition(Node *dest, int x, int y);
    //void deprecateLabel(float time);
    //void setPhysicsWorld(PhysicsWorld* world);
    //void addEdge();
    void showPauseScreen();
    void hidePauseScreen();
    void configTilePhysics(int x, int y, PhysicsBody * body);
    void configPlayerPhysics(int p, PhysicsBody * body);
    void configEdgePhysics(PhysicsBody * body);
    void updatePlayerZ();
    void placeBubble(int x, int y, PhysicsBody * body, float time);
    void addProps(int x, int y, const std::string & filename, PhysicsBody * body);
    void playMovingAnimation(int p, int d);
    void stopMovingAnimation(int p);
    void playHurtAnimation(int p);
    void playerDie(int p);
    void playerProtected(int p, bool protect);
    void addWave(Vec2 start, Vec2 end, float show, float live, const std::string & filename, PhysicsBody * body);
private:
    GameSceneControllerDelegate * controller;
    BackgroundLayer * backgroundLayer;
    HudLayer * hudLayer;
    ObjectsLayer * objectsLayer;
    Sprite * pauseScreen;
    Vec2 vo;
    Size vs;
};

#endif // !__GAME_SCENE_VIEW_H__
