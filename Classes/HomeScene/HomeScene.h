#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HomeScene : public Layer {
public:
	static Scene * createScene();
	CREATE_FUNC(HomeScene)
	virtual bool init();

private:
    // Callbacks
	void onStartGameClick(Ref * sender);
    void onHelpGameClick(Ref * sender);
	void onAboutGameClick(Ref * sender);
	void onExitGameClick(Ref * sender);
    bool onPopupScreenTouchBegan(Touch * touch, Event * e);

    Sprite * popupScreen;

	Size vs;
	Vec2 vo;
};

#endif // !__HOME_SCENE_H__
