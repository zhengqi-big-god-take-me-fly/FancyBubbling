#ifndef __GAME_SCENE_CONTROLLER_H__
#define __GAME_SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "GameSceneControllerDelegate.h"
#include "GameSceneModel.h"

USING_NS_CC;

class GameSceneController : public Scene, public GameSceneControllerDelegate {
public:
	// Instantialize a Controller as Scene, used by Director.
	static Scene * createScene();
	// Custom create function.
	//static GameSceneController * create(GameSceneView * _view = nullptr);
    CREATE_FUNC(GameSceneController);
	virtual bool init();
    virtual void onExit();
private:
    void gameReady();
    void onCountdown(float delta);

	GameSceneView * view;
    GameSceneModel * model;

    int countdown;
};

#endif // !__GAME_SCENE_CONTROLLER_H__
