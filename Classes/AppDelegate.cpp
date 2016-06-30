#include "AppDelegate.h"
#include "HomeScene/HomeScene.h"
#include "SimpleAudioEngine.h"
#include "Utils/Utils.h"

USING_NS_CC;

using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("FancyBubbling", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);

    director->setDepthTest(true);

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    FileUtils::getInstance()->addSearchPath("res");
    FileUtils::getInstance()->addSearchPath("maps");

    // Load animations
    auto sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("protected.plist");
    Utils::loadAnimation("protected", "protected-%d.png", 0, 14, 1.0f / 10);

    // Load sfx
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sfx/background-music.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx/bubble-explosion-sound.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx/place-bubble.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx/use-props-sound.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx/start-sound.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx/count-sound.wav");

    // create a scene. it's an autorelease object
    auto scene = HomeScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
     SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
