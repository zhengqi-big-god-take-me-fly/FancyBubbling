#ifndef __GAME_SCENE_VIEW_H__
#define __GAME_SCENE_VIEW_H__

#include "cocos2d.h"
#include "GameSceneControllerDelegate.h"
#include "View/BackgroundLayer.h"
#include "View/HudLayer.h"
#include "View/ObjectsLayer.h"

USING_NS_CC;

/*
Node to hold all Layers and prepare callbacks.
*/
class GameSceneView : public Node {
public:
    static GameSceneView * create(GameSceneControllerDelegate * _controller, PhysicsWorld * _world);
    virtual bool init(GameSceneControllerDelegate * _controller, PhysicsWorld * _world);
private:
    GameSceneControllerDelegate * controller;
    BackgroundLayer * backgroundLayer;
    HudLayer * hudLayer;
    ObjectsLayer * objectsLayer;
    Vec2 vo;
    Size vs;
};

#endif // !__GAME_SCENE_VIEW_H__
