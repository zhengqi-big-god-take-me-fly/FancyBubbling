#ifndef __GAME_SCENE_CONTROLLER_H__
#define __GAME_SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "GameSceneControllerDelegate.h"
#include "GameSceneModel.h"
#include "GameSceneView.h"

USING_NS_CC;

#define KEY_MEDICINE "MEDICINE"
#define KEY_SHIELD "SHIELD"

class GameSceneController : public Scene, public GameSceneControllerDelegate {
public:
    // Constants
    const static int GROUP_PLAYER = 1;
    const static int GROUP_BLOCK = 2;
    const static int GROUP_WALL = 3;
    const static int GROUP_BUBBLE = 4;
    const static int GROUP_WAVE = 5;
    const static int GROUP_PROPS = 6;
    // Inherited from Scene
	static Scene * createScene();       // Instantialize a Controller as Scene, used by Director.
    static GameSceneController * createWithPhysics();
	virtual bool init();
    virtual void onExit();
    virtual void update(float delta);
    // Inherited from GameSceneControllerDelegate
    virtual void bubbleExplode(Node * node);
private:
    // Should be in Model
    BlockModel * getBlock(Vec2 v);
    // Helper functions
    void gameReady();
    void gameStart();
    bool playerPresolve(Node * player);
    void playerSeparate(Node * player);
    bool isPlayerAndBody(int a, int b);
    void changePlayerDirection(int p, PlayerModel::Direction d);
    void placeBubble(int p);
    void useProps(int p, const char * k);
    void playerBeAttacked(int p);
    void playerGetProps(int p, Node * pr);
    void blockBeAttacked(Node * b);
    
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
