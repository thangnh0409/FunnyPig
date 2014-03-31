#pragma once
#include "cocos2d.h"
USING_NS_CC;
class ViewResult : public Layer
{
public:
    virtual bool init();  
    
    // a selector callback
    void backToMenuCallback(Object* pSender);
	void restartCallback(Object* pSender);
	void shareCallback(Object* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(ViewResult);
private:
	MenuItemImage* resultDialog;
	Sprite* star1;
	Sprite* star2;
	Sprite* star3;
    LabelTTF* lbScore;
    LabelTTF* lbBestScore;
protected :

};
