#ifndef __GAME_SCENE_CONTROLLER_H__
#define __GAME_SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "GameSceneControllerDelegate.h"
#include "GameSceneModel.h"
#include "GameSceneView.h"

USING_NS_CC;

class GameSceneController : public Scene, public GameSceneControllerDelegate {
public:
	static Scene * createScene();       // Instantialize a Controller as Scene, used by Director.
    CREATE_FUNC(GameSceneController);
	virtual bool init();
    virtual void onExit();
private:
    void gameReady();
    //void onCountdown(float delta);

    // Callbacks
    void keyboardOnKeyPressed(EventKeyboard::KeyCode code, Event * e);
    void keyboardOnKeyReleased(EventKeyboard::KeyCode code, Event * e);
    void countdownOnChanged(EventCustom * e);
    // Memeber variables
    GameSceneView * view;
    GameSceneModel * model;
};

#endif // !__GAME_SCENE_CONTROLLER_H__
