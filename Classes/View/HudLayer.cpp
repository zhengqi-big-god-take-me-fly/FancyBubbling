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
	player_1_itemButton_1->setAnchorPoint(Vec2(0.5f, 0));
	player_1_itemButton_1->setPosition(origin.x + 96, origin.y + 398);
	addChild(player_1_itemButton_1);


    player_1_itemHolder_2 = Sprite::create("game-props-box.png");
    player_1_itemHolder_2->setAnchorPoint(Vec2(0, 0));
    player_1_itemHolder_2->setPosition(origin.x + 58, origin.y + 188);
    addChild(player_1_itemHolder_2);
	player_1_itemButton_2 = Sprite::create("SHIELD-ui.png");
	player_1_itemButton_2->setAnchorPoint(Vec2(0.5f, 0));
	player_1_itemButton_2->setPosition(origin.x + 96, origin.y + 230);
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
	player_2_itemButton_1->setAnchorPoint(Vec2(0.5f, 0));
	player_2_itemButton_1->setPosition(origin.x + layerSize.width - 96, origin.y + 398);
	addChild(player_2_itemButton_1);
	player_2_itemButton_2 = Sprite::create("SHIELD-ui.png");
	player_2_itemButton_2->setAnchorPoint(Vec2(0.5f, 0));
	player_2_itemButton_2->setPosition(origin.x + layerSize.width - 96, origin.x + 230);
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

	Sprite * hpbar = Sprite::create("hp-foreground.png");
	hps.pushBack(hpbar);
	ProgressTimer * timer = ProgressTimer::create(hpbar);
	timer->setAnchorPoint(Vec2(0.5f, 0));
	timer->setPosition(origin.x + 36, origin.y + 164);
    timer->setType(ProgressTimerType::BAR);
    timer->setBarChangeRate(Vec2(0, 1));
    timer->setMidpoint(Vec2(0, 0));
    timer->setPercentage(100);
	addChild(timer);
	hpTimers.pushBack(timer);

	hpbar = Sprite::create("hp-foreground.png");
	hps.pushBack(hpbar);
	timer = ProgressTimer::create(hpbar);
	timer->setAnchorPoint(Vec2(0.5f, 0));
	timer->setPosition(origin.x + layerSize.width - 36, origin.y + 164);
    timer->setType(ProgressTimerType::BAR);
    timer->setBarChangeRate(Vec2(0, 1));
    timer->setMidpoint(Vec2(0, 0));
    timer->setPercentage(100);
	addChild(timer);
	hpTimers.pushBack(timer);



    warningMessage = Label::createWithTTF("按Esc键打开菜单", "fonts/theme-font.ttf", 20, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
    warningMessage->setPosition(origin.x + layerSize.width / 2, origin.y + 28);
    addChild(warningMessage);

    props[0][0] = Label::createWithTTF("", "fonts/theme-font.ttf", 36, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
    props[0][0]->setPosition(origin.x + 96, origin.y + 377);
    addChild(props[0][0]);
    props[0][1] = Label::createWithTTF("", "fonts/theme-font.ttf", 36, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
    props[0][1]->setPosition(origin.x + 96, origin.y + 209);
    addChild(props[0][1]);
    props[1][0] = Label::createWithTTF("", "fonts/theme-font.ttf", 36, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
    props[1][0]->setPosition(origin.x + layerSize.width - 96, origin.y + 377);
    addChild(props[1][0]);
    props[1][1] = Label::createWithTTF("", "fonts/theme-font.ttf", 36, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
    props[1][1]->setPosition(origin.x + layerSize.width - 96, origin.y + 209);
    addChild(props[1][1]);

    return true;
}

void HudLayer::setHP(int p, int hp, int maxHp)
{
	if (p < 0 || p > 2 || p > hps.size()) return;
	(hpTimers.at(p))->setPercentage(float(hp) / maxHp * 100);
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

void HudLayer::setPropsCount(int p, int i, int c) {
    props[p][i]->setString(std::to_string(c));
}
