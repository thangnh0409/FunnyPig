#include "ViewResult.h"
#include "StartScreen.h"
#include "GameHud.h"
#include "HelloWorldScene.h"

USING_NS_CC;
 
// on "init" you need to initialize your instance
bool ViewResult::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	resultDialog = MenuItemImage::create(
                                           "result.png",
                                           "result.png",
                                           CC_CALLBACK_1(ViewResult::backToMenuCallback, this));
	resultDialog->setPosition(Point(origin.x+visibleSize.width/2,
		origin.y + visibleSize.height/2));
	auto menuResultDialog = Menu::create(resultDialog, NULL);
    menuResultDialog->setPosition(Point::ZERO);
    this->addChild(menuResultDialog,0);
	
	

	star1 = Sprite::create("star1.png");
	star1->setPosition(Point(visibleSize.width/2 + origin.x -star1->getContentSize().width/2 , visibleSize.height/2 + origin.y+ star1->getContentSize().height + 50));
	star1->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(1.0f, 0.7), ScaleTo::create(1.0f, 0.6), NULL)));
    this->addChild(star1, 2);
	star1->setVisible(false);

	star2 = Sprite::create("star1.png");
    star2->setPosition(Point(visibleSize.width/2 +origin.x+star2->getContentSize().width/5, visibleSize.height/2 + origin.y+ star2->getContentSize().height + 50));
	star2->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(1.0f, 0.7), ScaleTo::create(1.0f, 0.6), NULL)));
    this->addChild(star2, 2);
	star2->setVisible(false);
	star3 = Sprite::create("star1.png");
    star3->setPosition(Point(visibleSize.width/2 + origin.x+star1->getContentSize().width/1.1f, visibleSize.height/2 + origin.y+ star3->getContentSize().height + 50));
	star3->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(1.0f, 0.7), ScaleTo::create(1.0f, 0.6), NULL)));
    this->addChild(star3, 2);
	star3->setVisible(false);

	
	UserDefault* res = UserDefault::getInstance();
	int bestScore = res->getIntegerForKey("HIGH_SCORE",0);
	int score = GameHUD::shareInstance()->getGameScore();
    log("game score: %d", score);
	if(score < 50)
	{
		star1->setVisible(true);
	}
	else if(score > 50 && score < 100)
	{
		star1->setVisible(true);
		star2->setVisible(true);
	}
	else
	{
		star1->setVisible(true);
		star2->setVisible(true);
		star3->setVisible(true);
	}

    /* add label score and best score **/
    lbScore = LabelTTF::create(String::createWithFormat("%d", score)->getCString(), "fonts/Softplain.ttf", 120);
    lbScore->setPosition(Point(visibleSize.width/2 + 50, visibleSize.height/2 + 30));
    lbScore->setColor(Color3B(151, 85, 7));
    lbScore->setAnchorPoint(Point::ZERO);
    this->addChild(lbScore);
    lbBestScore = LabelTTF::create(String::createWithFormat("%d", bestScore)->getCString(), "fonts/Softplain.ttf", 120);
    lbBestScore->setPosition(lbScore->getPosition() - Point(0, lbBestScore->getContentSize().height + 35));
    lbBestScore->setAnchorPoint(Point::ZERO);
    lbBestScore->setColor(Color3B(151, 85, 7));
    this->addChild(lbBestScore);

	auto share = MenuItemImage::create(
                                           "facebook-share-button.png",
                                           "facebook-share-button.png",
                                           CC_CALLBACK_1(ViewResult::shareCallback, this));
	share->setPosition(resultDialog->getPosition() - Point(share->getContentSize().width/3*share->getScaleX() + resultDialog->getContentSize().width/4*resultDialog->getScaleX(), resultDialog->getContentSize().height/4*resultDialog->getScaleY() + share->getContentSize().height/3*share->getScaleY()));
	auto menuShareDialog = Menu::create(share, NULL);
    menuShareDialog->setPosition(Point::ZERO);
    menuShareDialog->setVisible(false);
    this->addChild(menuShareDialog, 1);

    /** add button restart**/
	auto restart = MenuItemImage::create("circle1.png",
                                         "circle2.png",
                                         CC_CALLBACK_1(ViewResult::restartCallback, this));
	//restart->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
	restart->setPosition(resultDialog->getPosition() + Point(share->getContentSize().width/3*share->getScaleX() + resultDialog->getContentSize().width/4*resultDialog->getScaleX(), -resultDialog->getContentSize().height/4*resultDialog->getScaleY() - share->getContentSize().height/3*share->getScaleY()));
	auto menuRestartDialog = Menu::create(restart, NULL);
    menuRestartDialog->setPosition(Point::ZERO);
    //this->addChild(menuRestartDialog, 1);
    
    return true;
}



void ViewResult::backToMenuCallback(Object* pSender)
{
	Scene *pScene = StartScreen::createScene();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5f,pScene));
}

void ViewResult::restartCallback(Object* pSender)
{
	Scene *pScene = StartScreen::createScene();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5f,pScene));
}

void ViewResult::shareCallback(Object* pSender)
{
	
}
