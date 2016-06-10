#ifndef __PLAYER_MODEL_H__
#define __PLAYER_MODEL_H__

#include "cocos2d.h"
#include <map>

USING_NS_CC;

//#define PLAYER_DIRECTION_CHANGED_EVENT "player direction changed"

class ItemModel;

class PlayerModel : public Ref {
public :
    
    typedef enum {
        dead,
        invincible,
        alive
    } Status;
    
    typedef enum {
        still,
        up,
        down,
        left,
        right
    } Direction;
    
    CREATE_FUNC(PlayerModel);
    virtual bool init();
    
//  玩家当前方向
    CC_PROPERTY(Direction, _direction, Direction);
    
//  玩家当前速度，由direction和speed直接计算得出，不可设置
    CC_SYNTHESIZE_READONLY(Vec2, _velocity, Velocity);
    
//  玩家所在位置
    CC_SYNTHESIZE(Vec2, _position, Position);
    
//  玩家血量
    CC_PROPERTY(float, _hp, Hp);
    float addHp(float var);
    
//  玩家状态
    CC_SYNTHESIZE(Status, _status, Status);
    
//    玩家速度
    CC_SYNTHESIZE(float, _speed, Speed);
    float addSpeedByRate(float rate);
    
//    玩家可放置泡泡数量
    CC_SYNTHESIZE(int, _shootRate, ShootRate);
    int addShootRate(int var);
    
//    玩家放置的泡泡的爆炸延迟
    CC_SYNTHESIZE(float, _blowDelay, BlowDelay);
    unsigned int addBlowDelay(int var);
    
//    玩家放置的泡泡的爆炸范围
    CC_SYNTHESIZE(unsigned int, _blowRange, BlowRange);
    unsigned int addBlowRange(int var);
    
//    玩家拥有的道具
    std::map<std::string, int> items;
    
protected :
};

#endif /* __PLAYER_MODEL_H__ */
