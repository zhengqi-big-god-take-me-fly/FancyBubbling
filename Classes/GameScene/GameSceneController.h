#ifndef __GAME_SCENE_CONTROLLER_H__
#define __GAME_SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "GameSceneControllerDelegate.h"
#include "GameSceneView.h"

USING_NS_CC;

class GameSceneController : public Scene, public GameSceneControllerDelegate {
public:
	// Instantialize a Controller as Scene, used by Director.
	static Scene * createScene();
	// Custom create function.
	static GameSceneController * create(GameSceneView * _view = nullptr);
	virtual bool init(GameSceneView * _view);
	// TODO
private:
	GameSceneView * view;
};

#endif // !__GAME_SCENE_CONTROLLER_H__
