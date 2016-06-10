#include "GameSceneController.h"
#include "GameSceneView.h"

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
    auto countdownListener = EventListenerCustom::create("Countdown", CC_CALLBACK_1(GameSceneController::countdownOnChanged, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(countdownListener, this);
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
    //model->addPlayer(0);
    //model->addPlayer(1);
    //view->addPlayer(0);
    //view->addPlayer(1);

    // Load hud
    //view->setAvatar(0, "player0.png");
    //view->setAvatar(1, "player1.png");
    //view->setHP(0, model->getPlayer(0)->getHP(), model->getPlayer(0)->getMaxHP());
    //view->setHP(1, model->getPlayer(1)->getHP(), model->getPlayer(1)->getMaxHP());
    //view->setPropsCount(0, 0, 0);
    //view->setPropsCount(0, 1, 0);
    //view->setPropsCount(1, 0, 0);
    //view->setPropsCount(1, 1, 0);
}

bool GameSceneController::playerPresolve(int p, PhysicsBody * playerBody, PhysicsContact & contact) {
    //switch (model->getPlayerModel(p)->getMovingdirection()) {
    //case PlayerModel::MovingDirection::Up:
    //case PlayerModel::MovingDirection::Down:
    //    playerBody->setVelocity(Vec2(playerBody->getVelocity().x, model->getPlayerModel(p)->getVelocity().y));
    //    return true;
    //case PlayerModel::MovingDirection::Left:
    //case PlayerModel::MovingDirection::Right:
    //    playerBody->setVelocity(Vec2(model->getPlayerModel(p)->getVelocity().x, playerBody->getVelocity().y));
    //    return true;
    //case PlayerModel::MovingDirection::None:
    //    playerBody->setVelocity(Vec2::ZERO);
    //    return false;
    //default:
    //    return false;
    //}
}

void GameSceneController::playerSeparate(int p, PhysicsBody * playerBody) {
    //playerBody->setVelocity(model->getPlayerModel(p)->getVelocity());
}

//void GameSceneController::changePlayerDirection(int p, PlayerModel::MovingDirection d) {
//    model->getPlayerModel(p)->setDirection(d);
//    view->setPlayerVelocity(p, model->getPlayerModel(p)->getVelocity());
//}

//GameSceneController::CollisionType GameSceneController::getCollisionType(int tag1, int tag2) {}

void GameSceneController::keyboardOnKeyPressed(EventKeyboard::KeyCode code, Event * e) {
    switch (code) {
    // Player1
    case EventKeyboard::KeyCode::KEY_E:
        //changePlayerDirection(0, PlayerModel::MovingDirection::Up);
        break;
    case EventKeyboard::KeyCode::KEY_D:
        //changePlayerDirection(0, PlayerModel::MovingDirection::Down);
        break;
    case EventKeyboard::KeyCode::KEY_S:
        //changePlayerDirection(0, PlayerModel::MovingDirection::Left);
        break;
    case EventKeyboard::KeyCode::KEY_F:
        //changePlayerDirection(0, PlayerModel::MovingDirection::Right);
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
        break;
    case EventKeyboard::KeyCode::KEY_Q:
        break;
    case EventKeyboard::KeyCode::KEY_R:
        break;
    // Player2
    case EventKeyboard::KeyCode::KEY_I:
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        //changePlayerDirection(1, PlayerModel::MovingDirection::Up);
        break;
    case EventKeyboard::KeyCode::KEY_K:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        //changePlayerDirection(1, PlayerModel::MovingDirection::Down);
        break;
    case EventKeyboard::KeyCode::KEY_J:
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        //changePlayerDirection(1, PlayerModel::MovingDirection::Left);
        break;
    case EventKeyboard::KeyCode::KEY_L:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        //changePlayerDirection(1, PlayerModel::MovingDirection::Right);
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
        //if (model->getPlayer(0)->getMovingDirection() == PlayerModel::MovingDirection::Up)
        //    changePlayerDirection(0, PlayerModel::MovingDirection::None);
        break;
    case EventKeyboard::KeyCode::KEY_D:
        //if (model->getPlayer(0)->getMovingDirection() == PlayerModel::MovingDirection::Down)
        //    changePlayerDirection(0, PlayerModel::MovingDirection::None);
        break;
    case EventKeyboard::KeyCode::KEY_S:
        //if (model->getPlayer(0)->getMovingDirection() == PlayerModel::MovingDirection::Left)
        //    changePlayerDirection(0, PlayerModel::MovingDirection::None);
        break;
    case EventKeyboard::KeyCode::KEY_F:
        //if (model->getPlayer(0)->getMovingDirection() == PlayerModel::MovingDirection::Right)
        //    changePlayerDirection(0, PlayerModel::MovingDirection::None);
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
        //if (model->getPlayer(1)->getMovingDirection() == PlayerModel::MovingDirection::Up)
        //    changePlayerDirection(1, PlayerModel::MovingDirection::None);
        break;
    case EventKeyboard::KeyCode::KEY_K:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        //if (model->getPlayer(1)->getMovingDirection() == PlayerModel::MovingDirection::Down)
        //    changePlayerDirection(1, PlayerModel::MovingDirection::None);
        break;
    case EventKeyboard::KeyCode::KEY_J:
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        //if (model->getPlayer(1)->getMovingDirection() == PlayerModel::MovingDirection::Left)
        //    changePlayerDirection(1, PlayerModel::MovingDirection::None);
        break;
    case EventKeyboard::KeyCode::KEY_L:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        //if (model->getPlayer(1)->getMovingDirection() == PlayerModel::MovingDirection::Right)
        //    changePlayerDirection(1, PlayerModel::MovingDirection::None);
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

void GameSceneController::countdownOnChanged(EventCustom * e) {
    // TODO: Get countdown from e
    int countdown = 0;
    if (countdown <= 0) {
        // TODO: Interface Request
        // void notifyReady(const std::string &);
        //view->notifyReady("START!");
        //unschedule(schedule_selector(GameSceneController::onCountdown));
    } else {
        // TODO: Interface Request
        //view->notifyReady(std::to_string(countdown));
    }
}

//void GameSceneController::playingMovingOnDirectionChanged(EventCustom * e) {
//    // TODO: Get player and direction from e.
//}
