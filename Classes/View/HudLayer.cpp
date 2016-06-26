#include "HudLayer.h"

Scene * HudLayer::createScene() {
	auto scene = Scene::create();
	auto layer = HudLayer::create();
	scene->addChild(layer);
	return scene;
}

bool HudLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	origin = Director::getInstance()->getVisibleOrigin();
	layerSize = Director::getInstance()->getVisibleSize();

	//HUd Has no Background
	//backgroundImage = Sprite::create("game-area-background.png");

	/*Size t = backgroundImage->getContentSize();
	
	backgroundImage->setScale((layerSize.width / t.width) * (layerSize.height / t.height));
	backgroundImage->setPosition(origin.x + layerSize.width / 2, origin.y + layerSize.height / 2);

	addChild(backgroundImage);*/

	player_1_leftItemHolder = Sprite::create("game-props-box.png");
	//player_1_leftItemHolder->setContentSize(Size(72,144));
	player_1_leftItemHolder->setPosition(origin.x + 58, origin.y + 188);



	player_1_rightItemHolder = Sprite::create("game-props-box.png");
	//player_1_rightItemHolder->setContentSize(Size(72, 144));
	player_1_rightItemHolder->setPosition(origin.x + layerSize.width - 130 , origin.y + 188);



	player_2_leftItemHolder = Sprite::create("game-props-box.png");
	//player_2_leftItemHolder->setContentSize(Size(72, 144));
	player_2_leftItemHolder->setPosition(origin.x + 58, origin.y + 356);


	player_2_rightItemHolder = Sprite::create("game-props-box.png");
	player_2_rightItemHolder->setPosition(origin.x + layerSize.width - 130, origin.y + 356);


	//player_2_rightItemHolder->setContentSize(Size(72, 144));
	 //player_1_leftItemButton;
	 //player_1_rightItemButton;
	 //player_2_leftItemButton;
	 //player_2_rightItemButton;

	//deprecated
	 /*menuButton = MenuItemImage::create(
		 "game-menu-button-normal.png",
		 "game-menu-button-pressed.png",
		 CC_CALLBACK_1(HudLayer::menuCloseCallback, this));
	 menuButton -> setPosition(Vec2(origin.x + layerSize.width - menuButton->getContentSize().width / 2,
		 origin.y + menuButton->getContentSize().height / 2));*/

	 player1Icon = Sprite::create("hp-background-0.png");
	 //player1Icon->setContentSize(Size(108, 108));
	 player1Icon->setPosition(origin.x + 24, origin.y + 56);
	 avatar1 = Sprite::create("avatar-0.png");
	 avatar1->setPosition(origin.x + 24, origin.y + 56);


	 player2Icon = Sprite::create("hp-background-1.png");
	 //player1Icon->setContentSize(Size(108, 108));
	 player1Icon->setPosition(origin.x + layerSize.width - 156 , origin.y + 56);
	 avatar2 = Sprite::create("avatar-2.png");
	 avatar2->setPosition(origin.x + layerSize.width - 156, origin.y + 56);
	 



	 hpBar1 = Sprite::create("hp-foreground.png");
	 //hpBar1->setContentSize(Size(16, 450));
	 hpBar1->setPosition(origin.x + 28, origin.y + 56);

	 hpBar2 = Sprite::create("hp-foreground.png");
	 //hpBar1->setContentSize(Size(16, 450));
	 hpBar1->setPosition(origin.x + layerSize.width - 44 , origin.y + 56);


	 warningMessage = Label::createWithTTF("Press Esc To open Menu", "fonts/Marker Felt.ttf", 20);
	 warningMessage->setPosition(origin.x + layerSize.width / 2 - warningMessage->getContentSize().width / 2 , origin.y + 10);

	return true;
}

void HudLayer::menuCloseCallback(Ref * pSender)
{
	// Implemented By Controller
}




#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif

