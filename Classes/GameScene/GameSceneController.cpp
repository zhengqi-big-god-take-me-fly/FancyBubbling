#include "GameSceneController.h"

Scene * GameSceneController::createScene() {
	return GameSceneController::createWithPhysics();
}

GameSceneController * GameSceneController::createWithPhysics() {
    GameSceneController *ret = new (std::nothrow) GameSceneController();
    if (ret && ret->initWithPhysics()) {
        ret->autorelease();
        return ret;
    } else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool GameSceneController::init() {
    // View initialization
	view = GameSceneView::create(this);
	addChild(view);
    
    // Model initialization
    model = GameSceneModel::create();
    model->retain();                    // Controller retains model instance.

    // EventListeners
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(GameSceneController::keyboardOnKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GameSceneController::keyboardOnKeyReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, -1);
    auto spritePhysicsListener = EventListenerPhysicsContact::create();
    spritePhysicsListener->onContactBegin = CC_CALLBACK_1(GameSceneController::spriteOnContactBegin, this);
    spritePhysicsListener->onContactPreSolve = CC_CALLBACK_2(GameSceneController::spriteOnContactPreSolve, this);
    spritePhysicsListener->onContactSeparate = CC_CALLBACK_1(GameSceneController::spriteOnContactSeparate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(spritePhysicsListener, this);

    gameReady();

    scheduleUpdate();

	return true;
}

void GameSceneController::onExit() {
    unscheduleUpdate();
    model->release();
    Scene::onExit();
}

void GameSceneController::update(float delta) {
}

void GameSceneController::bubbleExplode(Node * node) {}

bool GameSceneController::spriteOnContactBegin(PhysicsContact & contact) {
    auto sa = contact.getShapeA()->getBody()->getNode();
    auto sb = contact.getShapeB()->getBody()->getNode();
    auto gra = contact.getShapeA()->getBody()->getGroup();
    auto grb = contact.getShapeB()->getBody()->getGroup();

    // Player and block
    if (isPlayerAndBody(gra, grb)) {
        return true;
    }
    
    // Player and wave
    if (gra == GROUP_WAVE && grb == GROUP_PLAYER) {
        //playerBeAttacked(view->getPlayerId(sb));
    } else if (grb == GROUP_WAVE && gra == GROUP_PLAYER) {
        //playerBeAttacked(view->getPlayerId(sa));
    }

    // Player and props
    if (gra == GROUP_PLAYER && grb == GROUP_PROPS) {
        //playerGetProps(view->getPlayerId(sa), sb);
    } else if (gra == GROUP_PROPS && grb == GROUP_PLAYER) {
        //playerGetProps(view->getPlayerId(sb), sa);
    }

    // Wave and block
    if (gra == GROUP_WAVE && grb == GROUP_BLOCK) {
        blockBeAttacked(sb);
    } else if (gra == GROUP_BLOCK && grb == GROUP_WAVE) {
        blockBeAttacked(sa);
    }

    // Wave and bubble
    if (gra == GROUP_WAVE && grb == GROUP_BUBBLE) {
        bubbleExplode(sb);
    } else if (gra == GROUP_BUBBLE && grb == GROUP_WAVE) {
        bubbleExplode(sa);
    }

    return false;
}

bool GameSceneController::spriteOnContactPreSolve(PhysicsContact & contact, PhysicsContactPreSolve & solve) {
    auto gra = contact.getShapeA()->getBody()->getGroup();
    auto grb = contact.getShapeB()->getBody()->getGroup();

    if (isPlayerAndBody(gra, grb)) {
        playerPresolve(gra == GROUP_PLAYER ? contact.getShapeA()->getBody()->getNode() : contact.getShapeB()->getBody()->getNode());
    }

    return true;
}

void GameSceneController::spriteOnContactSeparate(PhysicsContact & contact) {
    auto gra = contact.getShapeA()->getBody()->getGroup();
    auto grb = contact.getShapeB()->getBody()->getGroup();

    if (isPlayerAndBody(gra, grb)) {
        playerSeparate(gra == GROUP_PLAYER ? contact.getShapeA()->getBody()->getNode() : contact.getShapeB()->getBody()->getNode());
    }
}

void GameSceneController::gameReady() {
    // TODO
    // Load ui
    //view->loadUI();

    // Load map
    //model->prepareMap("garden.json");
    //view->addMap("garden.tmx");

    // Add players
    model->players.push_back(PlayerModel::create());
    model->players.push_back(PlayerModel::create());
    //view->addPlayer(0);
    //view->addPlayer(1);

    // Load hud
    //view->setAvatar(0, "player0.png");
    //view->setAvatar(1, "player1.png");
    //view->setHP(0, model->players[0]->getHP(), model->players[0]->getMaxHP());
    //view->setHP(1, model->players[1]->getHP(), model->players[1]->getMaxHP());
    //view->setPropsCount(0, 0, 0);
    //view->setPropsCount(0, 1, 0);
    //view->setPropsCount(1, 0, 0);
    //view->setPropsCount(1, 1, 0);

    // Start countdown
    model->setTime(3);
    model->setStatus(GameSceneModel::Status::ready);
    schedule(schedule_selector(GameSceneController::countdown, this), 1, 4, 1.0f / 60);
}

void GameSceneController::gameStart() {
    model->setStatus(GameSceneModel::Status::running);
}

bool GameSceneController::playerPresolve(Node * player) {
    //int p = view->getPlayerId(player);
    //auto body = player->getPhysicsBody();
    //switch (model->players[p]->getDirection()) {
    //case PlayerModel::Direction::up:
    //case PlayerModel::Direction::down:
    //    body->setVelocity(Vec2(body->getVelocity().x, model->players[p]->getVelocity().y));
    //    return true;
    //case PlayerModel::Direction::left:
    //case PlayerModel::Direction::right:
    //    body->setVelocity(Vec2(model->players[p]->getVelocity().x, body->getVelocity().y));
    //    return true;
    //case PlayerModel::Direction::still:
    //    body->setVelocity(Vec2::ZERO);
    //    return false;
    //default:
    //    return false;
    //}
    return false;
}

void GameSceneController::playerSeparate(Node * player) {
    //int p = view->getPlayerId(player);
    //player->getPhysicsBody()->setVelocity(model->players[p]->getVelocity());
}

bool GameSceneController::isPlayerAndBody(int a, int b) {
    return (a == GROUP_PLAYER && (b == GROUP_BLOCK || b == GROUP_WALL || b == GROUP_BUBBLE))
        || (b == GROUP_PLAYER && (a == GROUP_BLOCK || a == GROUP_WALL || a == GROUP_BUBBLE));
}

void GameSceneController::changePlayerDirection(int p, PlayerModel::Direction d) {
    model->players[p]->setDirection(d);
    //view->setPlayerVelocity(p, model->players[p]->getVelocity());
}

void GameSceneController::placeBubble(int p) {}

void GameSceneController::useProps(int p, int i) {}

void GameSceneController::playerBeAttacked(int p) {}

void GameSceneController::playerGetProps(int p, Node * pr) {}

void GameSceneController::blockBeAttacked(Node * b) {}

void GameSceneController::countdown(float delta) {
    int time = model->getTime();
    if (time <= 0) {
        // TODO: Interface Request
        // void notifyReady(const std::string &);
        //view->notifyReady("START!");
        unschedule(schedule_selector(GameSceneController::countdown));
        gameStart();
    } else {
        // TODO: Interface Request
        //view->notifyReady(std::to_string(time));
        model->setTime(time - 1);
    }
}

void GameSceneController::keyboardOnKeyPressed(EventKeyboard::KeyCode code, Event * e) {
    switch (code) {
    // Player0
    case EventKeyboard::KeyCode::KEY_E:
        changePlayerDirection(0, PlayerModel::Direction::up);
        break;
    case EventKeyboard::KeyCode::KEY_D:
        changePlayerDirection(0, PlayerModel::Direction::down);
        break;
    case EventKeyboard::KeyCode::KEY_S:
        changePlayerDirection(0, PlayerModel::Direction::left);
        break;
    case EventKeyboard::KeyCode::KEY_F:
        changePlayerDirection(0, PlayerModel::Direction::right);
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
        placeBubble(0);
        break;
    case EventKeyboard::KeyCode::KEY_Q:
        useProps(0, 0);
        break;
    case EventKeyboard::KeyCode::KEY_R:
        useProps(0, 1);
        break;
    // Player1
    case EventKeyboard::KeyCode::KEY_I:
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        changePlayerDirection(1, PlayerModel::Direction::up);
        break;
    case EventKeyboard::KeyCode::KEY_K:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        changePlayerDirection(1, PlayerModel::Direction::down);
        break;
    case EventKeyboard::KeyCode::KEY_J:
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        changePlayerDirection(1, PlayerModel::Direction::left);
        break;
    case EventKeyboard::KeyCode::KEY_L:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        changePlayerDirection(1, PlayerModel::Direction::right);
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
    case EventKeyboard::KeyCode::KEY_0:
        placeBubble(1);
        break;
    case EventKeyboard::KeyCode::KEY_U:
    case EventKeyboard::KeyCode::KEY_1:
        useProps(1, 0);
        break;
    case EventKeyboard::KeyCode::KEY_O:
    case EventKeyboard::KeyCode::KEY_2:
        useProps(1, 1);
        break;
    // Default
    default:
        break;
    }
}

void GameSceneController::keyboardOnKeyReleased(EventKeyboard::KeyCode code, Event * e) {
    switch (code) {
    // Player0
    case EventKeyboard::KeyCode::KEY_E:
        if (model->players[0]->getDirection() == PlayerModel::Direction::up)
            changePlayerDirection(0, PlayerModel::Direction::still);
        break;
    case EventKeyboard::KeyCode::KEY_D:
        if (model->players[0]->getDirection() == PlayerModel::Direction::down)
            changePlayerDirection(0, PlayerModel::Direction::still);
        break;
    case EventKeyboard::KeyCode::KEY_S:
        if (model->players[0]->getDirection() == PlayerModel::Direction::left)
            changePlayerDirection(0, PlayerModel::Direction::still);
        break;
    case EventKeyboard::KeyCode::KEY_F:
        if (model->players[0]->getDirection() == PlayerModel::Direction::right)
            changePlayerDirection(0, PlayerModel::Direction::still);
        break;
    // Player1
    case EventKeyboard::KeyCode::KEY_I:
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        if (model->players[1]->getDirection() == PlayerModel::Direction::up)
            changePlayerDirection(1, PlayerModel::Direction::still);
        break;
    case EventKeyboard::KeyCode::KEY_K:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        if (model->players[1]->getDirection() == PlayerModel::Direction::down)
            changePlayerDirection(1, PlayerModel::Direction::still);
        break;
    case EventKeyboard::KeyCode::KEY_J:
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        if (model->players[1]->getDirection() == PlayerModel::Direction::left)
            changePlayerDirection(1, PlayerModel::Direction::still);
        break;
    case EventKeyboard::KeyCode::KEY_L:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        if (model->players[1]->getDirection() == PlayerModel::Direction::right)
            changePlayerDirection(1, PlayerModel::Direction::still);
        break;
    // Default
    default:
        break;
    }
}
