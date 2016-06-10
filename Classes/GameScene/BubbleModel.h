#ifndef __BUBBLE_MODEL_H__
#define __BUBBLE_MODEL_H__

#include "cocos2d.h"
#include "BlockModel.h"

#define BUBBLE_BLOW_EVENT "bubble blow"

USING_NS_CC;

class PlayerModel;

class BubbleModel: public BlockModel {
public :
    
    CREATE_FUNC(BubbleModel);
    virtual bool init();
    
    CC_SYNTHESIZE(float, _blowDelay, BlowDelay);
    CC_SYNTHESIZE(int, _blowRange, BlowRange);
    CC_SYNTHESIZE(PlayerModel *, _owner, Owner);

    void beginBlowUp() const;
    
};

#endif /* __BUBBLE_MODEL_H__ */
