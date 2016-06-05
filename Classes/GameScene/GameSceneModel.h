#ifndef __GAME_SCENE_MODEL_H__
#define __GAME_SCENE_MODEL_H__

#include "cocos2d.h"

USING_NS_CC;

class GameSceneModel : public Ref {
public:
    // Notes:
    // Rewrite this method if you need some parameters to init.
    CREATE_FUNC(GameSceneModel);
    virtual bool init();
private:
};

#endif // !__GAME_SCENE_MODEL_H__
