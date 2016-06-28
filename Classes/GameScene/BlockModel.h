#ifndef __BLOCK_MODEL_H__
#define __BLOCK_MODEL_H__

#include "cocos2d.h"
#include <string>
#include <map>

USING_NS_CC;

class BlockModel : public Ref {
public :
    CREATE_FUNC(BlockModel);
    virtual bool init();
    
    static bool registerBlock(BlockModel * block, const std::string & key);
    
    static BlockModel * create(const std::string & key);
    
    CC_SYNTHESIZE(Vec2, _position, Position);
    CC_SYNTHESIZE(Texture2D *, _texture, Texture);
    CC_SYNTHESIZE_READONLY(std::string, _key, Key);
    
    CC_SYNTHESIZE(bool, _breakable, Breakable);
    CC_SYNTHESIZE(bool, _blockWave, BlockWave);
    
    virtual ~BlockModel() {}
    
protected :
    
    static std::map<std::string, BlockModel> _registPool;
};

#endif /* __BLOCK_MODEL_H__ */
