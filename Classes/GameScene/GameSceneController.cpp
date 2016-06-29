#include "GameSceneController.h"
#include "BubbleModel.h"
#include "ItemModel.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Scene * GameSceneController::createScene() {
	auto scene = GameSceneController::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    return scene;
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

bool GameSceneController::initWithPhysics() {
    if (!Scene::initWithPhysics()) {
        return false;
    }

    // View initialization
    view = GameSceneView::create(this, getPhysicsWorld());
    addChild(view);

    // Model initialization
    model = GameSceneModel::create();
    model->retain();                    // Controller retains model instance.

    // EventListeners
    keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(GameSceneController::keyboardOnKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GameSceneController::keyboardOnKeyReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, -1);
    spritePhysicsListener = EventListenerPhysicsContact::create();
    spritePhysicsListener->onContactBegin = CC_CALLBACK_1(GameSceneController::spriteOnContactBegin, this);
    spritePhysicsListener->onContactPreSolve = CC_CALLBACK_2(GameSceneController::spriteOnContactPreSolve, this);
    spritePhysicsListener->onContactSeparate = CC_CALLBACK_1(GameSceneController::spriteOnContactSeparate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(spritePhysicsListener, this);

    gameReady();

    scheduleUpdate();

    if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("sfx/background-music.wav", true);

    return true;
}

void GameSceneController::onExit() {
    unscheduleUpdate();
    _eventDispatcher->removeEventListener(keyboardListener);
    _eventDispatcher->removeEventListener(spritePhysicsListener);
    model->release();
    Scene::onExit();
}

void GameSceneController::update(float delta) {
    view->updatePlayerZ();
}

void GameSceneController::bubbleExplode(Node * node) {
    auto gp = view->getGridPosition(node);
    auto bubble = (BubbleModel *)model->getMap(gp.x, gp.y);
    auto range = bubble->getBlowRange();
    Vec2 md[4] = { Vec2(0, -1), Vec2(1, 0), Vec2(0, 1), Vec2(-1, 0) };  // 4 directions: Up, Right, Down, Left
    for (int d = 0; d < 4; ++d) {
        auto rp = gp;
        for (int r = 0; r < range; ++r) {
            rp += md[d];
            if (rp.x < 0 || rp.x > 14 || rp.y < 0 || rp.y > 12
                || (model->getMap(rp.x, rp.y) != nullptr && model->getMap(rp.x, rp.y)->getKey().compare(KEY_EMPTY) == false && model->getMap(rp.x, rp.y)->getBreakable() == false)) {
                rp -= md[d];
                break;
            }
            if (model->getMap(rp.x, rp.y) != nullptr
                && model->getMap(rp.x, rp.y)->getKey().compare(KEY_EMPTY) == false
                && model->getMap(rp.x, rp.y)->getBreakable()
                && model->getMap(rp.x, rp.y)->getBlockWave()) break;
        }
        auto body = PhysicsBody::createCircle(10);
        body->setGroup(GROUP_WAVE);
        body->setCategoryBitmask(16);               // 010000
        body->setCollisionBitmask(0);               // 000000
        body->setContactTestBitmask(1 + 2 + 4 + 8); // 001111
        view->addWave(gp, rp, 0.2f, 0, "wave.png", body);
    }
    view->removeNode(node);
    ++bubble->getOwner()->items[KEY_BUBBLE];
    SimpleAudioEngine::getInstance()->playEffect("sfx/bubble-explosion-sound.mp3");
}

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
        playerBeAttacked(view->getPlayerId(sb));
    } else if (grb == GROUP_WAVE && gra == GROUP_PLAYER) {
        playerBeAttacked(view->getPlayerId(sa));
    }

    // Player and props
    if (gra == GROUP_PLAYER && grb == GROUP_PROPS) {
        playerGetProps(view->getPlayerId(sa), sb);
    } else if (gra == GROUP_PROPS && grb == GROUP_PLAYER) {
        playerGetProps(view->getPlayerId(sb), sa);
    }

    // Wave and block
    if (gra == GROUP_WAVE && grb == GROUP_BLOCK) {
        blockBeAttacked(sb);
    } else if (gra == GROUP_BLOCK && grb == GROUP_WAVE) {
        blockBeAttacked(sa);
    }

    // Wave and wall
    if (gra == GROUP_WAVE && grb == GROUP_WALL) {
        sa->removeFromParent();
    } else if (gra == GROUP_WALL && grb == GROUP_WAVE) {
        sb->removeFromParent();
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
        // Fix bubble collision with user
        if (gra == GROUP_PLAYER && grb == GROUP_BUBBLE) {
            contact.getShapeB()->getBody()->setCollisionBitmask(1); // 001000
        } else if (gra == GROUP_BUBBLE && grb == GROUP_PLAYER) {
            contact.getShapeA()->getBody()->setCollisionBitmask(1); // 001000
        }
    }
}

void GameSceneController::gameReady() {
    // Load map
    loadMap("garden");

    // Register props
    registerProps();

    // Add 2 players
    addPlayers();

    // Load hud
    view->setHP(0, model->players.at(0)->getHp(), model->players.at(0)->MAX_HP);
    view->setHP(1, model->players.at(1)->getHp(), model->players.at(1)->MAX_HP);
    view->setPropsCount(0, 0, 0);
    view->setPropsCount(0, 1, 0);
    view->setPropsCount(1, 0, 0);
    view->setPropsCount(1, 1, 0);

    // Start countdown
    model->setTime(3);
    model->setStatus(GameSceneModel::Status::ready);
    schedule(schedule_selector(GameSceneController::countdown), 1, 4, 1.0f / 60);
}

void GameSceneController::gameStart() {
    model->setStatus(GameSceneModel::Status::running);
}

void GameSceneController::gamePause() {
    model->setStatus(GameSceneModel::Status::pause);
    // TODO: pause
    view->showPauseScreen();
}

void GameSceneController::gameResume() {
    model->setStatus(GameSceneModel::Status::running);
    // TODO: resume
    view->hidePauseScreen();
}

void GameSceneController::gameExit() {
    Director::getInstance()->popScene();
}

void GameSceneController::loadMap(const std::string & mapName) {
    model->readConfigFromFile("maps/" + mapName + ".json");
    view->useMap(("maps/" + mapName + ".tmx").c_str());
    for (unsigned x = 0; x < model->getMapSize().width; ++x) {
        for (int y = 0; y < model->getMapSize().height; ++y) {
            if (model->getMap(x, y) != nullptr && model->getMap(x, y)->getKey().compare("empty") != 0) {
                auto body = PhysicsBody::createBox(Size(40, 40));
                body->setDynamic(false);
                body->setGroup(model->getMap(x, y)->getBreakable() ? GROUP_BLOCK : GROUP_WALL);
                body->setCategoryBitmask(model->getMap(x, y)->getBreakable() ? 2 : 4);          // 000010 : 000100
                body->setCollisionBitmask(model->getMap(x, y)->getBreakable() ? 1 : 1);         // 000001 : 000001
                body->setContactTestBitmask(model->getMap(x, y)->getBreakable() ? 1 + 16 : 1 + 16);  // 010001 : 010001
                view->configTilePhysics(x, y, body);
            }
        }
    }
    auto edgeBody = PhysicsBody::createEdgeBox(Size(600, 520));
    edgeBody->setDynamic(false);
    edgeBody->setGroup(GROUP_WALL);
    edgeBody->setCategoryBitmask(4);    // 000100
    edgeBody->setCollisionBitmask(1);   // 000001
    edgeBody->setContactTestBitmask(1 + 16); // 010001
    view->configEdgePhysics(edgeBody);
}

void GameSceneController::registerProps() {
    Item * props;

    // EMPTY
    props = Item::create();
    props->setAppearRate(67);
    Item::registerItem(props, KEY_EMPTY);

    // BUBBLE
    props = Item::create();
    props->setAppearRate(0);
    Item::registerItem(props, KEY_BUBBLE);

    // MEDICINE
    props = Item::create();
    props->setAppearRate(16);
    props->setHpUp(30);
    Item::registerItem(props, KEY_MEDICINE);

    // SHIELD
    props = Item::create();
    props->setAppearRate(16);
    props->setOriginStatus(PlayerModel::Status::invincible);
    Item::registerItem(props, KEY_SHIELD);

    // BALLOON
    props = Item::create();
    props->setAppearRate(16);
    props->setShootRateUp(1);
    Item::registerItem(props, KEY_BALLOON);

    // POTION
    props = Item::create();
    props->setAppearRate(16);
    props->setBlowRangeUp(1);
    Item::registerItem(props, KEY_POTION);

    // SHOES
    props = Item::create();
    props->setAppearRate(16);
    props->setSpeedUp(2);
    Item::registerItem(props, KEY_SHOES);

    // TURTLE
    props = Item::create();
    props->setAppearRate(16);
    props->setAbleToHold(true);
    props->setSpeedUp(0.6f);
    Item::registerItem(props, KEY_TURTLE);
}

void GameSceneController::addPlayers() {
    auto p0 = PlayerModel::create();
    p0->setBlowDelay(3);
    p0->setBlowRange(1);
    p0->setDirection(PlayerModel::Direction::still);
    p0->setHp(100);
    //p0->setShootRate(1);
    p0->setSpeed(80);
    p0->setStatus(PlayerModel::Status::alive);
    p0->items.insert(std::make_pair(KEY_BUBBLE, 1));
    p0->items.insert(std::make_pair(KEY_MEDICINE, 0));
    p0->items.insert(std::make_pair(KEY_SHIELD, 0));
    p0->items.insert(std::make_pair(KEY_TURTLE, 0));
    model->players.pushBack(p0);
    view->addPlayer(0, 0, 0, "player-0");
    auto body0 = PhysicsBody::createCircle(18, PhysicsMaterial(1, 0, 0));
    body0->setGroup(GROUP_PLAYER);
    body0->setCategoryBitmask(1);                       // 000001
    body0->setCollisionBitmask(2 + 4 + 8);              // 001110
    body0->setContactTestBitmask(2 + 4 + 8 + 16 + 32);  // 111110
    body0->setRotationEnable(false);

    auto p1 = PlayerModel::create();
    p1->setBlowDelay(3);
    p1->setBlowRange(1);
    p1->setDirection(PlayerModel::Direction::still);
    p1->setHp(100);
    //p1->setShootRate(1);
    p1->setSpeed(80);
    p1->setStatus(PlayerModel::Status::alive);
    p1->items.insert(std::make_pair(KEY_BUBBLE, 1));
    p1->items.insert(std::make_pair(KEY_MEDICINE, 0));
    p1->items.insert(std::make_pair(KEY_SHIELD, 0));
    p1->items.insert(std::make_pair(KEY_TURTLE, 0));
    model->players.pushBack(p1);
    view->addPlayer(1, 14, 12, "player-1");
    view->configPlayerPhysics(0, body0);
    auto body1 = PhysicsBody::createCircle(18, PhysicsMaterial(1, 0, 0));
    body1->setGroup(GROUP_PLAYER);
    body1->setCategoryBitmask(1);                       // 000001
    body1->setCollisionBitmask(2 + 4 + 8);              // 001110
    body1->setContactTestBitmask(2 + 4 + 8 + 16 + 32);  // 111110
    body1->setRotationEnable(false);
    view->configPlayerPhysics(1, body1);
}

bool GameSceneController::playerPresolve(Node * player) {
    int p = view->getPlayerId(player);
    auto body = player->getPhysicsBody();
    switch (model->players.at(p)->getDirection()) {
    case PlayerModel::Direction::up:
    case PlayerModel::Direction::down:
        body->setVelocity(Vec2(body->getVelocity().x, model->players.at(p)->getVelocity().y));
        return true;
    case PlayerModel::Direction::left:
    case PlayerModel::Direction::right:
        body->setVelocity(Vec2(model->players.at(p)->getVelocity().x, body->getVelocity().y));
        return true;
    case PlayerModel::Direction::still:
        body->setVelocity(Vec2::ZERO);
        return false;
    default:
        return false;
    }
    return false;
}

void GameSceneController::playerSeparate(Node * player) {
    int p = view->getPlayerId(player);
    player->getPhysicsBody()->setVelocity(model->players.at(p)->getVelocity());
}

bool GameSceneController::isPlayerAndBody(int a, int b) {
    return (a == GROUP_PLAYER && (b == GROUP_BLOCK || b == GROUP_WALL || b == GROUP_BUBBLE))
        || (b == GROUP_PLAYER && (a == GROUP_BLOCK || a == GROUP_WALL || a == GROUP_BUBBLE));
}

void GameSceneController::changePlayerDirection(int p, PlayerModel::Direction d) {
    model->players.at(p)->setDirection(d);
    view->setPlayerVelocity(p, model->players.at(p)->getVelocity());
    // There is bug in playing animation on a sprite with physics body.
    //switch (d) {
    //case PlayerModel::Direction::up:
    //    view->playMovingAnimation(p, 0);
    //    break;
    //case PlayerModel::Direction::down:
    //    view->playMovingAnimation(p, 1);
    //    break;
    //case PlayerModel::Direction::left:
    //    view->playMovingAnimation(p, 2);
    //    break;
    //case PlayerModel::Direction::right:
    //    view->playMovingAnimation(p, 3);
    //    break;
    //case PlayerModel::Direction::still:
    //    view->stopMovingAnimation(p);
    //    break;
    //default:
    //    break;
    //}
}

void GameSceneController::placeBubble(int p) {
    if (model->players.at(p)->items[KEY_BUBBLE] > 0) {
        --model->players.at(p)->items[KEY_BUBBLE];
        auto pp = view->getPlayerGridPosition(p);
        auto bm = BubbleModel::create();
        bm->setBlowDelay(model->players.at(p)->getBlowDelay());
        bm->setBlowRange(model->players.at(p)->getBlowRange());
        bm->setOwner(model->players.at(p));
        model->setMap(pp.x, pp.y, bm);
        auto body = PhysicsBody::createCircle(18, PhysicsMaterial(1, 0, 0));
        body->setDynamic(false);
        body->setRotationEnable(false);
        body->setGroup(GROUP_BUBBLE);
        body->setCategoryBitmask(8);            // 001000
        body->setCollisionBitmask(0);           // 000000 Temp to fix bubble collision
        body->setContactTestBitmask(1 + 16);    // 010001
        view->placeBubble(pp.x, pp.y, body, model->players.at(p)->getBlowDelay());
        SimpleAudioEngine::getInstance()->playEffect("sfx/place-bubble.wav");
    }
}

void GameSceneController::useProps(int p, const char * k) {
    // TODO: Use props (TBD)
    if (model->players.at(p)->items[k] > 0) {
        --model->players.at(p)->items[k];
    }
}

void GameSceneController::playerBeAttacked(int p) {
    // Hard-coded damage
    model->players.at(p)->addHp(-10);
    view->playHurtAnimation(p);
}

void GameSceneController::playerGetProps(int p, Node * pr) {
    auto g = view->getGridPosition(pr);
    auto props = ((ItemBlockModel *)model->getMap(g.x, g.y))->getItem();
    if (props->getKey().compare(KEY_MEDICINE) == 0) {
        ++model->players.at(p)->items[KEY_MEDICINE];
        view->setPropsCount(p, 0, model->players.at(p)->items[KEY_MEDICINE]);
    } else if (props->getKey().compare(KEY_SHIELD) == 0) {
        ++model->players.at(p)->items[KEY_SHIELD];
        view->setPropsCount(p, 0, model->players.at(p)->items[KEY_SHIELD]);
    } if (props->getKey().compare(KEY_BALLOON) == 0) {
        ++model->players.at(p)->items[KEY_BUBBLE];
    } else {
        props->applyToPlayer(model->players.at(p), false);
    }
    // clean
    model->removeMap(g.x, g.y);
    view->removeNode(pr);
}

void GameSceneController::blockBeAttacked(Node * b) {
    auto g = view->getGridPosition(b);
    model->removeMap(g.x, g.y);
    view->removeTile(g.x, g.y);
    generateProps(g);
}

void GameSceneController::generateProps(Vec2 p) {
    auto props = Item::randomGenerate();
    if (props != nullptr && props->getKey().compare(KEY_EMPTY) != 0) {
        model->setMap(p.x, p.y, ItemBlockModel::create(props));
        auto body = PhysicsBody::createBox(Size(40, 40));
        body->setDynamic(false);
        body->setRotationEnable(false);
        body->setGroup(GROUP_PROPS);
        body->setCategoryBitmask(32);   // 100000
        body->setCollisionBitmask(0);   // 000000
        body->setContactTestBitmask(1); // 000001
        view->addProps(p.x, p.y, props->getKey() + ".png", body);
    }
}

void GameSceneController::countdown(float delta) {
    int time = model->getTime();
    if (time <= 0) {
        view->notifyReady("START!");
        unschedule(schedule_selector(GameSceneController::countdown));
        gameStart();
    } else {
        view->notifyReady(std::to_string(time).c_str());
        model->setTime(time - 1);
    }
}

void GameSceneController::keyboardOnKeyPressed(EventKeyboard::KeyCode code, Event * e) {
    if (model->getStatus() == model->pause) {
        if (code == EventKeyboard::KeyCode::KEY_ESCAPE) {
            gameExit();
        } else {
            gameResume();
        }
        return;
    } else if (model->getStatus() == model->running && code == EventKeyboard::KeyCode::KEY_ESCAPE) {
        gamePause();
        return;
    }
    switch (code) {
    // Player0
    case EventKeyboard::KeyCode::KEY_W:
        changePlayerDirection(0, PlayerModel::Direction::up);
        break;
    case EventKeyboard::KeyCode::KEY_S:
        changePlayerDirection(0, PlayerModel::Direction::down);
        break;
    case EventKeyboard::KeyCode::KEY_A:
        changePlayerDirection(0, PlayerModel::Direction::left);
        break;
    case EventKeyboard::KeyCode::KEY_D:
        changePlayerDirection(0, PlayerModel::Direction::right);
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
        if (model->getStatus() != GameSceneModel::Status::running) break;
        placeBubble(0);
        break;
    case EventKeyboard::KeyCode::KEY_Q:
        if (model->getStatus() != GameSceneModel::Status::running) break;
        useProps(0, KEY_MEDICINE);
        break;
    case EventKeyboard::KeyCode::KEY_E:
        if (model->getStatus() != GameSceneModel::Status::running) break;
        useProps(0, KEY_SHIELD);
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
        if (model->getStatus() != GameSceneModel::Status::running) break;
        placeBubble(1);
        break;
    case EventKeyboard::KeyCode::KEY_U:
    case EventKeyboard::KeyCode::KEY_1:
        if (model->getStatus() != GameSceneModel::Status::running) break;
        useProps(1, KEY_MEDICINE);
        break;
    case EventKeyboard::KeyCode::KEY_O:
    case EventKeyboard::KeyCode::KEY_2:
        if (model->getStatus() != GameSceneModel::Status::running) break;
        useProps(1, KEY_SHIELD);
        break;
    // Default
    default:
        break;
    }
}

void GameSceneController::keyboardOnKeyReleased(EventKeyboard::KeyCode code, Event * e) {
    switch (code) {
    // Player0
    case EventKeyboard::KeyCode::KEY_W:
        if (model->players.at(0)->getDirection() == PlayerModel::Direction::up) {
            changePlayerDirection(0, PlayerModel::Direction::still);
        }
        break;
    case EventKeyboard::KeyCode::KEY_S:
        if (model->players.at(0)->getDirection() == PlayerModel::Direction::down) {
            changePlayerDirection(0, PlayerModel::Direction::still);
        }
        break;
    case EventKeyboard::KeyCode::KEY_A:
        if (model->players.at(0)->getDirection() == PlayerModel::Direction::left) {
            changePlayerDirection(0, PlayerModel::Direction::still);
        }
        break;
    case EventKeyboard::KeyCode::KEY_D:
        if (model->players.at(0)->getDirection() == PlayerModel::Direction::right) {
            changePlayerDirection(0, PlayerModel::Direction::still);
        }
        break;
    // Player1
    case EventKeyboard::KeyCode::KEY_I:
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        if (model->players.at(1)->getDirection() == PlayerModel::Direction::up) {
            changePlayerDirection(1, PlayerModel::Direction::still);
        }
        break;
    case EventKeyboard::KeyCode::KEY_K:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        if (model->players.at(1)->getDirection() == PlayerModel::Direction::down) {
            changePlayerDirection(1, PlayerModel::Direction::still);
        }
        break;
    case EventKeyboard::KeyCode::KEY_J:
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        if (model->players.at(1)->getDirection() == PlayerModel::Direction::left) {
            changePlayerDirection(1, PlayerModel::Direction::still);
        }
        break;
    case EventKeyboard::KeyCode::KEY_L:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        if (model->players.at(1)->getDirection() == PlayerModel::Direction::right) {
            changePlayerDirection(1, PlayerModel::Direction::still);
        }
        break;
    // Default
    default:
        break;
    }
}
