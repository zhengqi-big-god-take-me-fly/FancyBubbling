#ifndef __GAME_SCENE_MODEL_H__
#define __GAME_SCENE_MODEL_H__

#include "cocos2d.h"
//#include "BubbleModel.h"
//#include "ItemModel.h"
#include "BlockModel.h"
#include "PlayerModel.h"

USING_NS_CC;

//class BlockModel;
//class PlayerModel;

class GameSceneModel : public Ref {
public:
    // Notes:
    // Rewrite this method if you need some parameters to init.
    CREATE_FUNC(GameSceneModel);
    virtual bool init();
    
    typedef enum {
        pause,   // 暂停
        ready,   // 准备
        running, // 正在进行
        stop     // 结束
    } Status;
    
    CC_SYNTHESIZE(Status, _status, Status);
    CC_SYNTHESIZE(float, _time, Time);

    std::vector<std::vector<BlockModel *> > map;
    std::vector<PlayerModel *> players;
    
protected :
    
};

#endif // !__GAME_SCENE_MODEL_H__
