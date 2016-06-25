
#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public Layer {
	public:
		static Scene * createScene();
		CREATE_FUNC(BackgroundLayer);
		virtual bool init();
	private:
		Sprite *backgroundImage;
		Vec2 layerAnchor;
		Vec2 backgroundPos;
		Vec2 origin;
		Size layerSize;
};

#endif // !__BACKGROUND_LAYER_H__
