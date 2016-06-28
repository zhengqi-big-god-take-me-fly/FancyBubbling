#include "PlayerModel.h"
#include "ItemModel.h"

bool PlayerModel::init() {
    _hp = DEFAULT_HP;
    _speed = DEFAULT_SPEED;
    _shootRate = DEFAULT_SHOOT_RATE;
    _status = Status::alive;
    return true;
}

void PlayerModel::setHp(float var) {
    _hp = fmax(MIN_HP, fmin(MAX_HP, var));
}

float PlayerModel::getHp() {
    return _hp;
}

float PlayerModel::addHp(float var) {
    setHp(getHp() + var);
    return _hp;
}

float PlayerModel::addSpeedByRate(float rate) {
    _speed += rate * DEFAULT_SPEED;
    return _speed;
}

int PlayerModel::addShootRate(int var) {
    _shootRate += var;
    return _shootRate;
}

unsigned int PlayerModel::addBlowDelay(int var) {
    _blowDelay += var;
    return _blowDelay;
}

unsigned int PlayerModel::addBlowRange(int var) {
    _blowRange += var;
    return _blowRange;
}

PlayerModel::Direction PlayerModel::getDirection() {
    return _direction;
}

void PlayerModel::setDirection(Direction var) {
    if (_direction != var) {
        _direction = var;
        switch (_direction) {
            case Direction::up:
                _velocity = Vec2(0, 1);
                break;
            case Direction::down:
                _velocity = Vec2(0, -1);
                break;
            case Direction::left:
                _velocity = Vec2(-1, 0);
                break;
            case Direction::right:
                _velocity = Vec2(1, 0);
                break;
            default:
                _velocity = Vec2::ZERO;
                break;
        }
        _velocity *= _speed;
//        EventCustom event(PLAYER_DIRECTION_CHANGED_EVENT);
//        event.setUserData((void *)this);
//        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
}

