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
    
    static void loadConfigFile(const std::string & path);
    
    CC_SYNTHESIZE(Vec2, _position, Position);
    CC_SYNTHESIZE(Texture2D *, _texture, Texture);
    CC_SYNTHESIZE_READONLY(std::string, _key, Key);
    
    bool isBreakable() const;
    bool isBlockWave() const;
    
protected :
    
    static std::map<std::string, BlockModel> _registPool;
    
    bool _breakable;
    bool _blockWave;
};

#endif /* __BLOCK_MODEL_H__ */
