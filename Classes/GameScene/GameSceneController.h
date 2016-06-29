#ifndef __GAME_SCENE_CONTROLLER_H__
#define __GAME_SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "GameSceneControllerDelegate.h"
#include "GameSceneModel.h"
#include "GameSceneView.h"

USING_NS_CC;

#define KEY_EMPTY "EMPTY"
#define KEY_BUBBLE "BUBBLE"
#define KEY_MEDICINE "MEDICINE"
#define KEY_SHIELD "SHIELD"
#define KEY_BALLOON "BALLOON"
#define KEY_POTION "POTION"
#define KEY_SHOES "SHOES"
#define KEY_TURTLE "TURTLE"

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
	//virtual bool init();
    virtual bool initWithPhysics();
    virtual void onExit();
    virtual void update(float delta);
    // Inherited from GameSceneControllerDelegate
    virtual void bubbleExplode(Node * node);
private:
    // Helper functions
    void gameReady();
    void gameStart();
    void gamePause();
    void gameResume();
    void gameEnd(int winner);
    void gameExit();
    void loadMap(const std::string & mapName);
    void registerProps();
    void addPlayers();
    bool playerPresolve(Node * player);
    void playerSeparate(Node * player);
    bool isPlayerAndBody(int a, int b);
    void changePlayerDirection(int p, PlayerModel::Direction d);
    void placeBubble(int p);
    void useProps(int p, const std::string & k);
    void playerBeAttacked(int p);
    void playerGetProps(int p, Node * pr);
    void blockBeAttacked(Node * b);
    void generateProps(Vec2 p);
    
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
    EventListenerKeyboard * keyboardListener;
    EventListenerPhysicsContact * spritePhysicsListener;
};

#endif // !__GAME_SCENE_CONTROLLER_H__
