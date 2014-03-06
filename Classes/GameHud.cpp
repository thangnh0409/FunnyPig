//
//  GameHud.cpp
//  FunnyPig
//
//  Created by thang nguyen on 3/5/14.
//
//

#include "GameHud.h"
#include "HelloWorldScene.h"

static GameHUD* _shareContext;

GameHUD* GameHUD::shareInstance()
{
    if (!_shareContext) {
        _shareContext = new GameHUD();
        _shareContext->init();
    }
    return _shareContext;
}

bool GameHUD::init()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto glView = EGLView::getInstance();
    Size frameSize = glView->getFrameSize();
    scaleFactor = MIN(frameSize.width/ 720, frameSize.height / 1280);
    scaleXFactor = frameSize.width/ 720;
    scaleYFactor = frameSize.height / 1280;
    time = 100;
    timerBar = ProgressTimer::create(Sprite::create("time.jpg"));
    timerBar->setScale(scaleXFactor, scaleYFactor);
    timerBar->setType(ProgressTimer::Type::BAR);
    timerBar->setPercentage(time);
    //timerBar->setAnchorPoint(Point::ZERO);
    timerBar->setBarChangeRate(Point(1, 0));
    timerBar->setMidpoint(Point(0, 0.5f));
    timerBar->setPosition(visibleSize.width/2, visibleSize.height - 160*scaleFactor);
    this->addChild(timerBar);
    
    auto timeFrameSprite = Sprite::create("time_frame.png");
    timeFrameSprite->setScale(scaleXFactor, scaleYFactor);
    timeFrameSprite->setPosition(timerBar->getPosition());
    this->addChild(timeFrameSprite);
    
    levelLabel = LabelTTF::create("Level 1", "Marker Felt", 40);
    levelLabel->setPosition(timeFrameSprite->getPosition());
    levelLabel->setColor(Color3B(26, 192, 18));
    this->addChild(levelLabel);
    
    scoreLabel = LabelTTF::create("0", "Marker Felt", 60);
    scoreLabel->setPosition(visibleSize.width/2, scoreLabel->getContentSize().height);
    scoreLabel->setColor(Color3B(50, 80, 255));
    this->addChild(scoreLabel);
    
    return true;
    
}


void GameHUD::updateTimerBar(int value)
{
    if (time > 0) {
        time = time - value;
    }
    timerBar->setPercentage(time);
}
void GameHUD::updateScore(int value)
{
    scoreLabel->setString(String::createWithFormat("%d", value)->getCString());
}
void GameHUD::updateLevel(int value)
{
    levelLabel->setString(String::createWithFormat("Level %d", value)->getCString());
}