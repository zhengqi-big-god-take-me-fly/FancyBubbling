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

	return true;
}

void GameSceneController::onExit() {
    model->release();
    Scene::onExit();
}
