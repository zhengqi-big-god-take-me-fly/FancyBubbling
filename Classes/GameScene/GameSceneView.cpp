#include "GameSceneView.h"

GameSceneView * GameSceneView::create(GameSceneControllerDelegate * _controller) {
    GameSceneView *pRet = new(std::nothrow) GameSceneView();
    if (pRet && pRet->init(_controller)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool GameSceneView::init(GameSceneControllerDelegate * _controller) {
    if (_controller == nullptr) return false;
    controller = _controller;
    return true;
}
