#include "GameSceneController.h"
#include "GameSceneView.h"

Scene * GameSceneController::createScene() {
	return GameSceneController::create();
}

//GameSceneController * GameSceneController::create(GameSceneView * _view) {
//	GameSceneController *pRet = new(std::nothrow) GameSceneController();
//	if (pRet && pRet->init(_view)) {
//		pRet->autorelease();
//		return pRet;
//	} else {
//		delete pRet;
//		pRet = nullptr;
//		return nullptr;
//	}
//}

bool GameSceneController::init() {
	view = GameSceneView::create(this);
	addChild(view);
    
    model = GameSceneModel::create();
    // Controller retains model instance.
    model->retain();

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
    view->initUIBackground();

    // Load map


    // Add players


    // Load hud


    // Countdown
    countdown = 4;
    schedule(schedule_selector(GameSceneController::onCountdown), 1, 4, 1.0f / 60);
}

void GameSceneController::onCountdown(float delta) {
    --countdown;
    if (countdown <= 0) {
        // TODO: Interface Request
        // void notifyReady(const std::string &);
        //view->notifyReady("START!");
        unschedule(schedule_selector(GameSceneController::onCountdown));
    } else {
        // TODO: Interface Request
        //view->notifyReady(std::to_string(countdown));
    }
}
