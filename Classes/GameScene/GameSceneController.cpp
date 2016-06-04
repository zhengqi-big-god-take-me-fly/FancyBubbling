#include "GameSceneController.h"

Scene * GameSceneController::createScene() {
	return GameSceneController::create(GameSceneView::create());
}

GameSceneController * GameSceneController::create(GameSceneView * _view) {
	GameSceneController *pRet = new(std::nothrow) GameSceneController();
	if (pRet && pRet->init(_view)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool GameSceneController::init(GameSceneView * _view) {
	view = _view;
	if (view != nullptr) {
		addChild(view);
	}
	return true;
}
