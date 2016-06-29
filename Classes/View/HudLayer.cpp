#include "HudLayer.h"

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

    player_1_itemHolder_1 = Sprite::create("game-props-box.png");
    player_1_itemHolder_1->setAnchorPoint(Vec2(0, 0));
    player_1_itemHolder_1->setPosition(origin.x + 58, origin.y + 356);
    addChild(player_1_itemHolder_1);
	player_1_itemButton_1 = Sprite::create("MEDICINE-ui.png");
	player_1_itemButton_1->setAnchorPoint(Vec2(0, 0));
	player_1_itemButton_1->setPosition(origin.x + 58, origin.y + 398);
	addChild(player_1_itemButton_1);


    player_1_itemHolder_2 = Sprite::create("game-props-box.png");
    player_1_itemHolder_2->setAnchorPoint(Vec2(0, 0));
    player_1_itemHolder_2->setPosition(origin.x + 58, origin.y + 188);
    addChild(player_1_itemHolder_2);
	player_1_itemButton_2 = Sprite::create("SHIELD-ui.png");
	player_1_itemButton_2->setAnchorPoint(Vec2(0, 0));
	player_1_itemButton_2->setPosition(origin.x + 58, origin.y + 230);
	addChild(player_1_itemButton_2);

    player_2_itemHolder_1 = Sprite::create("game-props-box.png");
    player_2_itemHolder_1->setAnchorPoint(Vec2(1, 0));
    player_2_itemHolder_1->setPosition(origin.x + layerSize.width - 58, origin.y + 188);
    addChild(player_2_itemHolder_1);


    player_2_itemHolder_2 = Sprite::create("game-props-box.png");
    player_2_itemHolder_2->setAnchorPoint(Vec2(1, 0));
    player_2_itemHolder_2->setPosition(origin.x + layerSize.width - 58, origin.y + 356);
    addChild(player_2_itemHolder_2);

	player_2_itemButton_1 = Sprite::create("MEDICINE-ui.png");
	player_2_itemButton_1->setAnchorPoint(Vec2(0, 0));
	player_2_itemButton_1->setPosition(origin.x + layerSize.width - 58, origin.y + 398);
	addChild(player_2_itemButton_1);
	player_2_itemButton_2 = Sprite::create("SHIELD-ui.png");
	player_2_itemButton_2->setAnchorPoint(Vec2(0, 0));
	player_2_itemButton_2->setPosition(origin.x + layerSize.width - 58, origin.x + 230);
	addChild(player_2_itemButton_2);


    //player_2_rightItemHolder->setContentSize(Size(72, 144));
    //player_1_leftItemButton;
    //player_1_rightItemButton;
    //player_2_leftItemButton;
    //player_2_rightItemButton;

    avatar1 = Sprite::create("avatar-0.png");
    avatar1->setAnchorPoint(Vec2(0, 0));
    avatar1->setPosition(origin.x + 24, origin.y + 56);
    addChild(avatar1);

    avatar2 = Sprite::create("avatar-1.png");
    avatar2->setAnchorPoint(Vec2(1, 0));
    avatar2->setPosition(origin.x + layerSize.width - 24, origin.y + 56);
    addChild(avatar2);

    hpBar1 = Sprite::create("hp-background-0.png");
    hpBar1->setAnchorPoint(Vec2(0, 1));
    hpBar1->setPosition(origin.x + 24, origin.y + layerSize.height - 16);
    addChild(hpBar1);

    hpBar2 = Sprite::create("hp-background-1.png");
    hpBar2->setAnchorPoint(Vec2(1, 1));
    hpBar2->setPosition(origin.x + layerSize.width - 24, origin.y + layerSize.height - 16);
    addChild(hpBar2);

    warningMessage = Label::createWithTTF("按Esc键打开菜单", "fonts/theme-font.ttf", 20, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
    warningMessage->setPosition(origin.x + layerSize.width / 2, origin.y + 28);
    addChild(warningMessage);

    return true;
}

void HudLayer::menuCloseCallback(Ref * pSender) {
    // Implemented By Controller
}
void HudLayer::displayItemCount(int player, int itemType, int count) {
	if (count < 0) return;
	char s[20];
	itoa(count, s, 10);

	auto itemCount = Label::createWithTTF(s, "fonts/theme-font.ttf", 15, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	itemCount->setAnchorPoint(Vec2(0, 0));
	
	int posX, posY;
	posX = origin.x + (player == 0 ? 58 : layerSize.width - 58);
	posY = origin.y + (itemType == 0 ? 458 : 290);
	
	itemCount->setPosition(Vec2(posX, posY));
	addChild(itemCount);
}