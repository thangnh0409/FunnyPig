#pragma once
#include "cocos2d.h"
USING_NS_CC;
class StartScreen : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
	void aboutCallback(Object* pSender);
	void infoCallback(Object* pSender);
	void playCallback(Object* pSender);
	void optionCallback(Object* pSender);
	void backToMenuCallback(Object* pSender);
    
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartScreen);
protected :
	Array * _map;/*
	Sprite* infoDialog;*/
	//MenuItemImage* backDialog;
	MenuItemImage* infoDialog;
	MenuItemImage* helpDialog;
};
