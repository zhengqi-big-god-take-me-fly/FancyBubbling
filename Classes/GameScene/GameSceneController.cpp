#include "GameSceneController.h"

Scene * GameSceneController::createScene() {
	return GameSceneController::create();
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
    //auto countdownListener = EventListenerCustom::create("Countdown", CC_CALLBACK_1(GameSceneController::countdownOnChanged, this));
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(countdownListener, this);
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
    model->release();
    Scene::onExit();
}

void GameSceneController::update(float delta) {
    //auto player0Grid = model->getMapModel()->coordinateToGrid(view->getPlayerPosition(0));
    //auto player1Grid = model->getMapModel()->coordinateToGrid(view->getPlayerPosition(1));
}

bool GameSceneController::spriteOnContactBegin(PhysicsContact & contact) {
    return false;
}

bool GameSceneController::spriteOnContactPreSolve(PhysicsContact & contact, PhysicsContactPreSolve & solve) {
    //auto grid0 = view->getGridPosition(contact.getShapeA()->getBody()->getNode());
    //auto grid1 = view->getGridPosition(contact.getShapeB()->getBody()->getNode());
    //int p0 = model->isPlayer(grid0);
    //int p1 = model->isPlayer(grid1);
    //if (p0 != -1) {
    //    return playerPresolve(p0, contact.getShapeA()->getBody(), contact);
    //} else if (p1 != -1) {
    //    return playerPresolve(p1, contact.getShapeB()->getBody(), contact);
    //} else {
    //    // TODO: Bubble explosion
    //}
    return true;
}

void GameSceneController::spriteOnContactSeparate(PhysicsContact & contact) {
    //auto grid0 = view->getGridPosition(contact.getShapeA()->getBody()->getNode());
    //auto grid1 = view->getGridPosition(contact.getShapeB()->getBody()->getNode());
    //int p0 = model->isPlayer(grid0);
    //int p1 = model->isPlayer(grid1);
    //if (p0 != -1) {
    //    return playerSeparate(p0, contact.getShapeA()->getBody());
    //} else if (p1 != -1) {
    //    return playerSeparate(p1, contact.getShapeB()->getBody());
    //}
}

void GameSceneController::gameReady() {
    // TODO
    // Load ui
    //view->loadUI();

    // Load map
    //model->prepareMap("some-map.mdj");
    //view->addMap("some-map.tmx");

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

bool GameSceneController::playerPresolve(int p, PhysicsBody * playerBody, PhysicsContact & contact) {
    //switch (model->getPlayerModel(p)->getDirection()) {
    //case PlayerModel::Direction::up:
    //case PlayerModel::Direction::down:
    //    playerBody->setVelocity(Vec2(playerBody->getVelocity().x, model->getPlayerModel(p)->getVelocity().y));
    //    return true;
    //case PlayerModel::Direction::left:
    //case PlayerModel::Direction::right:
    //    playerBody->setVelocity(Vec2(model->getPlayerModel(p)->getVelocity().x, playerBody->getVelocity().y));
    //    return true;
    //case PlayerModel::Direction::still:
    //    playerBody->setVelocity(Vec2::ZERO);
    //    return false;
    //default:
    //    return false;
    //}
    return false;
}

void GameSceneController::playerSeparate(int p, PhysicsBody * playerBody) {
    //playerBody->setVelocity(model->getPlayerModel(p)->getVelocity());
}

void GameSceneController::changePlayerDirection(int p, PlayerModel::Direction d) {
    model->players[p]->setDirection(d);
    //view->setPlayerVelocity(p, model->players[p]->getVelocity());
}

//GameSceneController::CollisionType GameSceneController::getCollisionType(int tag1, int tag2) {}

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
        break;
    case EventKeyboard::KeyCode::KEY_Q:
        break;
    case EventKeyboard::KeyCode::KEY_R:
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
        break;
    case EventKeyboard::KeyCode::KEY_U:
    case EventKeyboard::KeyCode::KEY_1:
        break;
    case EventKeyboard::KeyCode::KEY_O:
    case EventKeyboard::KeyCode::KEY_2:
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
    case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
        break;
    case EventKeyboard::KeyCode::KEY_Q:
        break;
    case EventKeyboard::KeyCode::KEY_R:
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
    case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
    case EventKeyboard::KeyCode::KEY_0:
        break;
    case EventKeyboard::KeyCode::KEY_U:
    case EventKeyboard::KeyCode::KEY_1:
        break;
    case EventKeyboard::KeyCode::KEY_O:
    case EventKeyboard::KeyCode::KEY_2:
        break;
        // Default
    default:
        break;
    }
}
