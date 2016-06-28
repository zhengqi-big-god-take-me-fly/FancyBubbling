#ifndef __PROP_MODEL_H__
#define __PROP_MODEL_H__

#include "cocos2d.h"
#include "PlayerModel.h"
#include "BlockModel.h"
//#include "BubbleModel.h"
#include <map>

USING_NS_CC;
using namespace std;

#define ITEM_TIME_OUT_EVENT "item time out"

class Item : public Ref {
    
public :
    CREATE_FUNC(Item);
    virtual bool init();
    
    static bool registerItem(Item * item, const std::string & key);
    
    static Item * create(const std::string & key);
    
    static void loadConfigFile(const std::string & path);
    
    CC_SYNTHESIZE(Texture2D *, _texture, Texture);
    
    CC_SYNTHESIZE(float, _speedUp, SpeedUp);
    CC_SYNTHESIZE(int, _shootRateUp, ShootRateUp);
    CC_SYNTHESIZE(float, _hpUp, HpUp);
    CC_SYNTHESIZE(float, _blowDelayUp, BlowDelayUp);
    CC_SYNTHESIZE(int, _blowRangeUp, BlowRangeUp);
    CC_SYNTHESIZE(PlayerModel::Status, _originStatus, OriginStatus);
    CC_SYNTHESIZE(PlayerModel::Status, _targetStatus, TargetStatus);
    
    CC_SYNTHESIZE(float, _activeDuration, ActiveDuration);
    CC_SYNTHESIZE(float, _appearRate, AppearRate);
    CC_SYNTHESIZE_READONLY(std::string, _key, Key);
    
    bool isAbleToHold() const;
    
    void setAbleToHold(bool flag);
    
    void applyToPlayer(PlayerModel * player, bool resume);
    
    static Item * randomGenerate();
    
protected :
    bool _canHold;
    
    static std::map<std::string, Item> _registPool;
    static float _totalAppearRate;
};

class ItemBlockModel: public BlockModel {
public :
    static ItemBlockModel * create(Item * item);
    
    virtual bool init(Item * item);
    
    CC_SYNTHESIZE_READONLY(Item *, _item, Item);
};

#endif /* __PROP_MODEL_H__ */
