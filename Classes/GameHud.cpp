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
    time = 100;
    maxTime = 100;
    timerBar = ProgressTimer::create(Sprite::create("time.jpg"));
    timerBar->setType(ProgressTimer::Type::BAR);
    timerBar->setPercentage(time);
    //timerBar->setAnchorPoint(Point::ZERO);
    timerBar->setBarChangeRate(Point(1, 0));
    timerBar->setMidpoint(Point(0, 0.5f));
    timerBar->setPosition(visibleSize.width/2, visibleSize.height - 160);
    this->addChild(timerBar);
    
    auto timeFrameSprite = Sprite::create("time_frame.png");
    timeFrameSprite->setPosition(timerBar->getPosition());
    this->addChild(timeFrameSprite);
    
    levelLabel = LabelTTF::create("Level 1", "fonts/Softplain.ttf", 60);
    levelLabel->setPosition(timeFrameSprite->getPosition());
    levelLabel->setColor(Color3B(26, 192, 18));
    this->addChild(levelLabel);
    
    scoreLabel = LabelTTF::create("0", "fonts/Softplain.ttf", 100);
    scoreLabel->setPosition(visibleSize.width/2, scoreLabel->getContentSize().height/2);
    scoreLabel->setColor(Color3B(242, 196, 13));
    this->addChild(scoreLabel);
    
    return true;
    
}

void GameHUD::reset()
{
    time = maxTime;
    _gameScore = 0;
    this->updateLevel(1);
    this->updateScore(0);
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
    _gameScore = value;
    scoreLabel->setString(String::createWithFormat("%d", _gameScore)->getCString());
}
void GameHUD::updateLevel(int value)
{
    levelLabel->setString(String::createWithFormat("Level %d", value)->getCString());
}