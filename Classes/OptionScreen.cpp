#include "OptionScreen.h"
#include "StartScreen.h"
#include "GameHud.h"
#include <SimpleAudioEngine.h>
USING_NS_CC;
 

Scene* OptionScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OptionScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OptionScreen::init()
{
    //////////////////////////////
    // 1. super init first
	enable = true;
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	float scale_button = 1.3f;

    auto sprite = Sprite::create("option.jpg");
	sprite->setAnchorPoint(Point::ZERO);
    sprite->setPosition(0,0);
    sprite->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);


	auto back = MenuItemImage::create(
                                           "cancel1.png",
                                           "cancel2.png",
                                           CC_CALLBACK_1(OptionScreen::backToMenuCallback, this));
	back->setScale(scale_button);
	back->setPosition(Point(origin.x + visibleSize.width - back->getContentSize().width ,
		origin.y + visibleSize.height- 1.5f*back->getContentSize().height));
	auto menuBack = Menu::create(back, NULL);
    menuBack->setPosition(Point::ZERO);
    this->addChild(menuBack, 1);


	auto music = MenuItemImage::create(
                                           "speaker_off.png",
                                           "speaker_off.png",
                                           CC_CALLBACK_1(OptionScreen::musicCallback, this));
	music->setPosition(Point(origin.x + visibleSize.width/2 ,
		origin.y + visibleSize.height/2- back->getContentSize().height));
	auto menuMusic = Menu::create(music, NULL);
    menuMusic->setPosition(Point::ZERO);
    this->addChild(menuMusic, 1);

	 music_on = Sprite::create("speaker_on.png");
                music_on->setPosition(Point(origin.x + visibleSize.width/2 ,
		origin.y + visibleSize.height/2- back->getContentSize().height));
                music_on->setTag(100);
                this->addChild(music_on);
    
    return true;
}




void OptionScreen::backToMenuCallback(Object* pSender)
{
	Scene *pScene = StartScreen::createScene();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5f,pScene));
}

void OptionScreen::musicCallback(Object* pSender)
{
	
	if(enable == true)
	{
		enable = false;
		music_on->setTexture("speaker_off.png");
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	else
	{
		enable = true;
		music_on->setTexture("speaker_on.png");
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}
