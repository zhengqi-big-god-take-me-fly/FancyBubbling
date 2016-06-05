#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HomeScene : public Layer {
public:
	static Scene * createScene();
	CREATE_FUNC(HomeScene);
	virtual bool init();
};

#endif // !__HOME_SCENE_H__
