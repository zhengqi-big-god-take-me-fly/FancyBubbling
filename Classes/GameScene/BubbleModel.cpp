#include "BubbleModel.h"
#include "PlayerModel.h"

bool BubbleModel::init() {
    _breakable = false;
    _key = "bubble";
    return true;
}

void BubbleModel::beginBlowUp() const {
    char key[32];
    sprintf(key, "%s %d", BUBBLE_BLOW_EVENT, _ID);
    Director::getInstance()->getScheduler()->schedule([=](float) {
        EventCustom event(BUBBLE_BLOW_EVENT);
        event.setUserData((void *)this);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }, (void *)this, 0, 0, _blowDelay, false, std::string(key));
}