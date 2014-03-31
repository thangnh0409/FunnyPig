#include "Splash.h"
#include "GameHud.h"
#include "StartScreen.h"

USING_NS_CC;

Scene* Splash::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Splash::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Splash::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("startup.jpg");
    sprite->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    schedule(schedule_selector(Splash::nextToMainScreen), 2.0f);
    
    return true;
}

void Splash::nextToMainScreen(float dt)
{
    auto screen = StartScreen::createScene();
    Director::getInstance()->replaceScene(CCTransitionFade::create(0.5f,screen));
}

