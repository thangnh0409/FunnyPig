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
    float scaleFactor;
    
    CC_SYNTHESIZE(int , time, Time);
    CC_SYNTHESIZE(float, scaleXFactor, ScaleXFactor);
    CC_SYNTHESIZE(float, scaleYFactor, ScaleYFactor);
    
    static GameHUD* shareInstance();
    bool init();
    void updateTimerBar(int value);
    void updateScore(int value);
    void updateLevel(int value);
};

#endif /* defined(__FunnyPig__GameHud__) */
