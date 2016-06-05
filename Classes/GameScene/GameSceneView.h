#ifndef __GAME_SCENE_VIEW_H__
#define __GAME_SCENE_VIEW_H__

#include "cocos2d.h"
#include "GameSceneControllerDelegate.h"

USING_NS_CC;

/*
Node to hold all Layers and prepare callbacks.
*/
class GameSceneView : public Node {
public:
    static GameSceneView * create(GameSceneControllerDelegate * _controller);
    virtual bool init(GameSceneControllerDelegate * _controller);
private:
    GameSceneControllerDelegate * controller;
};

#endif // !__GAME_SCENE_VIEW_H__
