#include "ItemModel.h"

std::map<std::string, Item> Item::_registPool;
float Item::_totalAppearRate = 0.0f;

bool Item::init() {
    return true;
}

bool Item::registerItem(Item * item, const std::string & key) {
    if (!item || _registPool.find(key) != _registPool.end()) {
        return false;
    }
    item->_key = key;
    _registPool[key] = *item;
    _totalAppearRate += item->getAppearRate();
    return true;
}

Item * Item::create(const std::string & key) {
    if (_registPool.find(key) != _registPool.end()) {
        Item * pRet = new Item(_registPool[key]);
        if (pRet) {
            pRet->autorelease();
            return pRet;
        }
    }
    return nullptr;
}

bool Item::isAbleToHold() const {
    return _canHold;
}

void Item::setAbleToHold(bool flag) {
    _canHold = flag;
}

void Item::applyToPlayer(PlayerModel * player, bool resume) {
    player->addSpeedByRate(_speedUp);
    player->addShootRate(_shootRateUp);
    player->addHp(_hpUp);
    player->addBlowDelay(_blowDelayUp);
    player->addBlowRange(_blowRangeUp);
    if (player->getStatus() == _originStatus) {
        player->setStatus(_targetStatus);
    }
    
    if (_activeDuration != 0.0) {
        char key[32];
        sprintf(key, "%s %d", ITEM_TIME_OUT_EVENT, _ID);
        Director::getInstance()->getScheduler()->schedule([=](float) {
            
            if (resume) {
                player->addSpeedByRate(-_speedUp);
                player->addShootRate(-_shootRateUp);
                player->addHp(-_hpUp);
                player->addBlowDelay(-_blowDelayUp);
                player->addBlowRange(-_blowRangeUp);
                if (player->getStatus() == _targetStatus) {
                    player->setStatus(_originStatus);
                }
            }
            
            EventCustom event(ITEM_TIME_OUT_EVENT);
            event.setUserData((void *)this);
            Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
            
        }, (void *)this, 0, 0, _activeDuration, false, std::string(key));
    }
}

Item * Item::randomGenerate() {
    float ran = random(0.0f, _totalAppearRate);
    for (auto it = _registPool.begin(); it != _registPool.end(); ++it) {
        if (ran > it->second.getAppearRate()) {
            ran -= it->second.getAppearRate();
        } else {
            return create(it->first);
        }
    }
    return nullptr;
}

ItemBlockModel * ItemBlockModel::create(Item * item) {
    ItemBlockModel * pRet = new ItemBlockModel();
    if (pRet && pRet->init(item)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool ItemBlockModel::init(Item * item) {
    if (!item) return false;
    _item = item;
    _texture = item->getTexture();
    _breakable = false;
    return true;
}