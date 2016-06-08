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

    gameReady();

	return true;
}

void GameSceneController::onExit() {
    model->release();
    Scene::onExit();
}

void GameSceneController::gameReady() {
    // TODO
    // Load ui
    //view->loadUI();

    // Load map


    // Add players


    // Load hud
}

void GameSceneController::keyboardOnKeyPressed(EventKeyboard::KeyCode code, Event * e) {
    switch (code) {
    // Player1
    case EventKeyboard::KeyCode::KEY_E:
        //model->getPlayer1()->setMovingDirection(PlayerModel::MovingDirection::Up);
        break;
    case EventKeyboard::KeyCode::KEY_D:
        break;
    case EventKeyboard::KeyCode::KEY_S:
        break;
    case EventKeyboard::KeyCode::KEY_F:
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
        break;
    case EventKeyboard::KeyCode::KEY_K:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        break;
    case EventKeyboard::KeyCode::KEY_J:
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        break;
    case EventKeyboard::KeyCode::KEY_L:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
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
        // Player1
    case EventKeyboard::KeyCode::KEY_E:
        //if (model->getPlayer1()->getMovingDirection() == PlayerModel::MovingDirection::Up)
        //    model->getPlayer1()->setMovingDirection(PlayerModel::MovingDirection::None);
        break;
    case EventKeyboard::KeyCode::KEY_D:
        break;
    case EventKeyboard::KeyCode::KEY_S:
        break;
    case EventKeyboard::KeyCode::KEY_F:
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
        break;
    case EventKeyboard::KeyCode::KEY_K:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        break;
    case EventKeyboard::KeyCode::KEY_J:
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        break;
    case EventKeyboard::KeyCode::KEY_L:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
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
