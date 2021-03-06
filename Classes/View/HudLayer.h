
#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class HudLayer : public Layer {
public:
	//static Scene * createScene();
	CREATE_FUNC(HudLayer)
	virtual bool init();
	void displayItemCount(int player, int itemType, int count);
	void menuCloseCallback(Ref *pSender);
	void setHP(int p, int hp, int maxHp);
    void setPropsCount(int p, int i, int c);
private:
	//Sprite *backgroundImage;

	Sprite *player_1_itemHolder_1;
	Sprite *player_1_itemHolder_2;
	Sprite *player_2_itemHolder_1;
	Sprite *player_2_itemHolder_2;
	
	Sprite *player_1_itemButton_1;
	Sprite *player_1_itemButton_2;
	Sprite *player_2_itemButton_1;
	Sprite *player_2_itemButton_2;

	//MenuItem *menuButton;
	//Menu *menu;

	//Sprite *player1Icon;
	//Sprite *player2Icon;

	Sprite *hpBar1;
	Sprite *hpBar2;

	Sprite *avatar1;
	Sprite *avatar2;

	Label *warningMessage;
    Label *props[2][2];

	Vec2 layerAnchor;
	Vec2 backgroundPos;
	Vec2 origin;
	Size layerSize;
	Vector<Node *> hps;
	Vector<ProgressTimer *> hpTimers;
};

#endif // !__HUD_LAYER_H__

