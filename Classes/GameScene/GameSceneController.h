#ifndef __GAME_SCENE_CONTROLLER_H__
#define __GAME_SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "GameSceneControllerDelegate.h"
#include "GameSceneModel.h"
#include "GameSceneView.h"

USING_NS_CC;

class GameSceneController : public Scene, public GameSceneControllerDelegate {
public:
    const static int TAG_PLAYER = 1;
    enum CollisionType { PlayerWall, PlayerBubble, PlayerBox };
	static Scene * createScene();       // Instantialize a Controller as Scene, used by Director.
    CREATE_FUNC(GameSceneController)
	virtual bool init();
    virtual void onExit();
    virtual void update(float delta);
private:
    void gameReady();
    void gameStart();
    bool playerPresolve(int p, PhysicsBody * playerBody, PhysicsContact & contact);
    void playerSeparate(int p, PhysicsBody * playerBody);
    void changePlayerDirection(int p, PlayerModel::Direction d);
    //CollisionType getCollisionType(int tag1, int tag2);
    
    // Schedulers
    void countdown(float delta);
    // Callbacks
    void keyboardOnKeyPressed(EventKeyboard::KeyCode code, Event * e);
    void keyboardOnKeyReleased(EventKeyboard::KeyCode code, Event * e);
    bool spriteOnContactBegin(PhysicsContact & contact);
    bool spriteOnContactPreSolve(PhysicsContact & contact, PhysicsContactPreSolve & solve);
    void spriteOnContactSeparate(PhysicsContact & contact);
    // Memeber variables
    GameSceneView * view;
    GameSceneModel * model;
};

#endif // !__GAME_SCENE_CONTROLLER_H__
