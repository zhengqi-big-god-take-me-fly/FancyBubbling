
#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class HudLayer : public Layer {
public:
	static Scene * createScene();
	CREATE_FUNC(HudLayer);
	virtual bool init();
private:
	Sprite *backgroundImage;
	
	Sprite *leftItemHolder;
	Sprite *rightItemHolder;
	
	Sprite *leftItemButton;
	Sprite *rightItemButton;

	Sprite *menuButton;

	Vec2 layerAnchor;
	Vec2 backgroundPos;
	Vec2 origin;
	Size layerSize;

};

#endif // !__HUD_LAYER_H__

