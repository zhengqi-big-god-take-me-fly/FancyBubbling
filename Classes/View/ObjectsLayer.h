
#ifndef __OBJECTS_LAYER_H__
#define __OBJECTS_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class ObjectsLayer : public Layer {
public:
	static Scene * createScene();
	CREATE_FUNC(ObjectsLayer);
	virtual bool init();
private:
	Sprite *backgroundImage;

	Sprite *player1;
	Sprite *player2;
	Vec2 player1_pos;
	Vec2 player2_pos;

	Sprite *map;
	Sprite *bubble1;
	Sprite *bubble2;

	Vec2 layerAnchor;
	Vec2 backgroundPos;
	Vec2 origin;
	Size layerSize;
};

#endif // !__OBJECTS_LAYER_H__

