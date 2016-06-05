#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HomeScene : public Layer {
public:
	static Scene * createScene();
	CREATE_FUNC(HomeScene);
	virtual bool init();

private:
	void onStartGameClick(Ref * sender);
	void onAboutGameClick(Ref * sender);
	void onExitGameClick(Ref * sender);

	Size vs;
	Vec2 vo;
};

#endif // !__HOME_SCENE_H__
