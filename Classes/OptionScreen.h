#pragma once
#include "cocos2d.h"
USING_NS_CC;
class OptionScreen : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void backToMenuCallback(Object* pSender);
	void musicCallback(Object* pSender);
	
    
    // implement the "static create()" method manually
	CREATE_FUNC(OptionScreen);
protected :
	Sprite* music_on;
	bool enable;

};
