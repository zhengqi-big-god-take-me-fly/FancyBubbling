#ifndef __FB_UTILS_H__
#define __FB_UTILS_H__

#include "cocos2d.h"

USING_NS_CC;

class Utils {
public:
    static void loadAnimation(const std::string & name, const std::string & format, int x, int y, float interval) {
        char frameName[128];
        auto a = Animation::create();
        for (int i = x; i <= y; ++i) {
            sprintf(frameName, format.c_str(), i);
            a->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
        }
        a->setDelayPerUnit(interval);
        AnimationCache::getInstance()->addAnimation(a, name);
    }
};

#endif // !__FB_UTILS_H__
