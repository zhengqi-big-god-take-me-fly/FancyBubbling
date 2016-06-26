#ifndef __GAME_SCENE_MODEL_H__
#define __GAME_SCENE_MODEL_H__

#include "cocos2d.h"
//#include "BubbleModel.h"
//#include "ItemModel.h"
#include "BlockModel.h"
#include "PlayerModel.h"
#include <fstream>
#include <map>
#include "json/rapidjson.h"
#include "json/document.h"

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

    std::vector<Vector<BlockModel *> > map;

    // 获取地图大小
    // 返回值 pair(column, row)
    Size getMapSize();

    // Remove specific tile from map
    bool removeMap(unsigned int column, unsigned int row);

    // Set block on specific tile
    bool setMap(unsigned int column, unsigned int row, BlockModel * block);

    //// 获取地图指定元素
    BlockModel * getMap(unsigned int column, unsigned int row);

    Vector<PlayerModel *> players;

    // 读取配置文件
    bool readConfigFromFile(const std::string & fileName);
protected:
};

#endif // !__GAME_SCENE_MODEL_H__
