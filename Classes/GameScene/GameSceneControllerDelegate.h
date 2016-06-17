#ifndef __GAME_SCENE_CONTROLLER_DELEGATE_H__
#define __GAME_SCENE_CONTROLLER_DELEGATE_H__

#include "cocos2d.h"

USING_NS_CC;

/*
Controller delegate to resolve cycle includings.
*/
class GameSceneControllerDelegate {
public:
    /*
    Invoked by View scheduler on bubble explosion.
    node    Bubble node.
    */
    virtual void bubbleExplode(Node * node) = 0;
};

#endif // !__GAME_SCENE_CONTROLLER_DELEGATE_H__
