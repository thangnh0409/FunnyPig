#include "StartScreen.h"
#include "HelloWorldScene.h"
#include "OptionScreen.h"
#include "SimpleAudioEngine.h"
#include "GameHud.h"

USING_NS_CC;
 

Scene* StartScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(StartScreen::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    
    /** play background music **/
    if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/nen.mp3", true);
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("start.jpg");
	sprite->setAnchorPoint(Point::ZERO);
    sprite->setPosition(0,0);
    sprite->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);


	auto about = MenuItemImage::create(
                                           "about1.png",
                                           "about2.png",
                                           CC_CALLBACK_1(StartScreen::aboutCallback, this));
	about->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
	about->setPosition(Point(origin.x+ about->getContentSize().width/2*about->getScaleX() ,
                                origin.y + about->getContentSize().height/2*getScaleY() ));
	auto menuAbout = Menu::create(about, NULL);
    menuAbout->setPosition(Point::ZERO);
    this->addChild(menuAbout, 1);


	auto info = MenuItemImage::create(
                                           "info1.png",
                                           "info2.png",
                                           CC_CALLBACK_1(StartScreen::infoCallback, this));
	info->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
	info->setPosition(Point(origin.x+visibleSize.width - info->getContentSize().width/2*info->getScaleX()  ,
                                origin.y + info->getContentSize().height/2*info->getScaleY()));
	auto menuInfo = Menu::create(info, NULL);
    menuInfo->setPosition(Point::ZERO);
    this->addChild(menuInfo, 1);


	auto play = MenuItemImage::create(
                                           "play3.png",
                                           "play4.png",
                                           CC_CALLBACK_1(StartScreen::playCallback, this));
	play->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
	play->setPosition(Point(origin.x +visibleSize.width/2,
                                origin.y + visibleSize.height/2));
	auto menuPlay = Menu::create(play, NULL);
    menuPlay->setPosition(Point::ZERO);
    this->addChild(menuPlay, 1);


	auto option = MenuItemImage::create(
                                           "option3.png",
                                           "option4.png",
                                           CC_CALLBACK_1(StartScreen::optionCallback, this));
	option->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
	option->setPosition(Point(play->getPosition() - Point(0, option->getContentSize().height*option->getScaleY() + 30)));
	auto menuOption = Menu::create(option, NULL);
    menuOption->setPosition(Point::ZERO);
    this->addChild(menuOption, 1);



	infoDialog = MenuItemImage::create(
                                           "info.png",
                                           "info.png",
                                           CC_CALLBACK_1(StartScreen::backToMenuCallback, this));
	infoDialog->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
	infoDialog->setPosition(Point(origin.x+visibleSize.width/2,origin.y + visibleSize.height/2));
	auto menuInfoDialog = Menu::create(infoDialog, NULL);
    menuInfoDialog->setPosition(Point::ZERO);
	//backDialog->setVisible(false);
    this->addChild(menuInfoDialog, 2);
	infoDialog->setVisible(false);


	helpDialog = MenuItemImage::create(
                                           "help.png",
                                           "help.png",
                                           CC_CALLBACK_1(StartScreen::backToMenuCallback, this));
	helpDialog->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
	helpDialog->setPosition(Point(origin.x+visibleSize.width/2,
		origin.y + visibleSize.height/2));
	auto menuHelpDialog = Menu::create(helpDialog, NULL);
    menuHelpDialog->setPosition(Point::ZERO);
    this->addChild(menuHelpDialog, 2);
	helpDialog->setVisible(false);
    
    return true;
}

void StartScreen::backToMenuCallback(Object *pSender)
{
	infoDialog->setVisible(false);
	helpDialog->setVisible(false);
}


void StartScreen::aboutCallback(Object *pSender)
{
	helpDialog->setVisible(true);

}

void StartScreen:: infoCallback(Object* pSender)
{
	infoDialog->setVisible(true);
}

void StartScreen:: playCallback(Object* pSender)
{
	Scene *pScene = HelloWorld::createScene();
	Director::getInstance()->pushScene(CCTransitionFade::create(0.5f,pScene));
}

void StartScreen:: optionCallback(Object* pSender)
{
	Scene *pScene = OptionScreen::createScene();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5f,pScene));
}
void StartScreen::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)
    {
        Director::getInstance()->end();
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_MENU)
    {
        log("MENU clicked!");
    }
}

