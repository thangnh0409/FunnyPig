//
//  GameHud.h
//  FunnyPig
//
//  Created by thang nguyen on 3/5/14.
//
//

#ifndef __FunnyPig__GameHud__
#define __FunnyPig__GameHud__

#include "cocos2d.h"


USING_NS_CC;

class GameHUD : public Layer{
    
public:
    
    ProgressTimer* timerBar;
    LabelTTF* scoreLabel;
    LabelTTF* levelLabel;
    
    CC_SYNTHESIZE(int , time, Time);
    CC_SYNTHESIZE(int, maxTime, MaxTime);
    CC_SYNTHESIZE(int , _gameScore, GameScore);
    CC_SYNTHESIZE(float, scaleXFactor, ScaleXFactor);
    CC_SYNTHESIZE(float, scaleYFactor, ScaleYFactor);
    CC_SYNTHESIZE(float, scaleFactor, ScaleFactor);
    
    static GameHUD* shareInstance();
    bool init();
    void reset();
    void updateTimerBar(int value);
    void updateScore(int value);
    void updateLevel(int value);
};

#endif /* defined(__FunnyPig__GameHud__) */
