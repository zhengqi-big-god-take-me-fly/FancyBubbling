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
	CREATE_FUNC(GameSceneView);
};

#endif // !__GAME_SCENE_VIEW_H__
