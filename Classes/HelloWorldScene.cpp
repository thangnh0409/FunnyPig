#include "HelloWorldScene.h"
#include "GameHud.h"
#include "ViewResult.h"
#include "SimpleAudioEngine.h"

#define DEFAULT_RETAIN          3
#define IMAGE_SIZE_WIDTH_MAX    150
#define IMAGE_SIZE_HEIGHT_MAX   150
#define MAX_WIDTH               4
#define MAX_HEIGHT              5

enum RANDOM_STATE {
    INCREMENT_WIDTH = 0,
    INCREMENT_HEIGHT = 1,
    UNCHANGE = 2
    };

enum GAME_STATE {
    RUNNING = 0,
    FINISH = 1
};

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    GameHUD* gh = GameHUD::shareInstance();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    scene->addChild(gh, 2);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    auto glView = EGLView::getInstance();
	Size frameSize = glView->getFrameSize();
    scaleFactor = MIN(frameSize.width/ 720, frameSize.height / 1280);
    background = Sprite::create("wallpaper.jpg");
    background->setPosition(visibleSize.width/2, visibleSize.height/2);
    background->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
    log("content scale: %f", scaleFactor);
    this->addChild(background, 0);
    
    auto bottomSprite = Sprite::create("bottom.png");
    bottomSprite->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
    bottomSprite->setPosition(visibleSize.width/2, bottomSprite->getContentSize().height/2 * GameHUD::shareInstance()->getScaleYFactor());
    //bottomSprite->setAnchorPoint(Point::ZERO);
    this->addChild(bottomSprite, 0);
    
    auto topSprite = Sprite::create("top.jpg");
    topSprite->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
    topSprite->setPosition(visibleSize.width/2, visibleSize.height - topSprite->getContentSize().height/2 * GameHUD::shareInstance()->getScaleYFactor());
    this->addChild(topSprite, 0);
    
    auto exitItem = MenuItemImage::create("cancel1.png", "cancel2.png", CC_CALLBACK_1(HelloWorld::onButtonExitClick, this));
    exitItem->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
    auto btnExit = Menu::create(exitItem, NULL);
    btnExit->setPosition(visibleSize.width - exitItem->getContentSize().width/2, visibleSize.height - exitItem->getContentSize().height/2);
    this->addChild(btnExit, 1);
    
    auto replayItem = MenuItemImage::create("circle1.png", "circle2.png", CC_CALLBACK_1(HelloWorld::onButtonReplayClick, this));
    replayItem->setScale(GameHUD::shareInstance()->getScaleXFactor(), GameHUD::shareInstance()->getScaleYFactor());
    btnReplay = Menu::create(replayItem, NULL);
    btnReplay->setPosition(replayItem->getContentSize().width/2, visibleSize.height - replayItem->getContentSize().height/2);
    this->addChild(btnReplay, 1);
    /**
     init map
     **/

    width = 2;
    height = 2;
    imageSizeHeight = IMAGE_SIZE_HEIGHT_MAX;
    imageSizeWidth = IMAGE_SIZE_WIDTH_MAX;
    retain = DEFAULT_RETAIN;
    for (int i = 0; i< 50; i++) {
        for (int j= 0; j<50; j++) {
            map[i][j] = 0;
        }
    }
    /* end init map */
    currentLevel = 1;
    currentRound = 1;
    gameState = RUNNING;
    isTouchRight = false;
    gameScore = 0;
    pics = new Array;
    pics->initWithCapacity(100);
    gridNode = NodeGrid::create();
    this->addChild(gridNode, 5);
    this->resetMap();
    this->drawMap();
    
    GameHUD::shareInstance()->reset();
    
    schedule(schedule_selector(HelloWorld::updateTimer), 0.1f);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    
    return true;
}

void HelloWorld::getNextLevel()
{
    currentLevel ++;
    GameHUD::shareInstance()->updateLevel(currentLevel);
    if (currentLevel % 5 == 0) {
        background->setTexture(String::createWithFormat("bg%d.jpg", arc4random()%4 + 1)->getCString());
        
    }
    if (currentLevel % 20 == 0) {
        getNextRound();
        return;
    }
    GameHUD::shareInstance()->setTime(getTimePlayByRound(currentRound));
    switch (arc4random()%4) {
        case INCREMENT_HEIGHT:
            if (height < MAX_HEIGHT) {
                height ++;
            }
            break;
        case INCREMENT_WIDTH:
            if (width < MAX_WIDTH) {
                width ++;
            }
            break;
        case UNCHANGE:
            break; 
            
        default:
            break;
    }
    
    isTouchRight = false;
    this->resetMap();
    this->drawMap();
    
    log("x= %d, y= %d", width, height);
}

void HelloWorld::getNextRound()
{
    currentRound ++;
    this->resetNewGame();
    this->drawMap();
    GameHUD::shareInstance()->setTime(getTimePlayByRound(currentRound));
}
void HelloWorld::drawMap()
{

    if (!gridNode) {
        gridNode = NodeGrid::create();
        this->addChild(gridNode, 5);
    }
    float scaleFactor = GameHUD::shareInstance()->getScaleFactor();
    
    if (height > width) {
        switch (height) {
            case 3:
                imageSizeHeight = imageSizeWidth = 250 * (scaleFactor - 0.1);
                break;
            case 4:
                imageSizeHeight = imageSizeWidth = 250 * (scaleFactor - 0.2);
                break;
            case 5:
                imageSizeHeight = imageSizeWidth = 250 * (scaleFactor - 0.3);
                break;
            default:
                imageSizeHeight = imageSizeWidth = 250 * scaleFactor;
                break;
        }
    }else{
        switch (width) {
            case 3:
                imageSizeHeight = imageSizeWidth = 250 * (scaleFactor - 0.1);
                break;
            case 4:
                imageSizeHeight = imageSizeWidth = 250 * (scaleFactor - 0.2);
                break;
            case 5:
                imageSizeHeight = imageSizeWidth = 250 * (scaleFactor - 0.3);
                break;
            default:
                imageSizeHeight = imageSizeWidth = 250 * scaleFactor;
                break;
        }

    }
    offsetRoot = Point(visibleSize.width/2 + imageSizeWidth/2, visibleSize.height/2 + imageSizeHeight/2) - Point(width * imageSizeWidth /2  , height* imageSizeHeight/2 );
    int offsetX = offsetRoot.x;
    int offsetY = offsetRoot.y;
    int randRotate = 0;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Sprite* sprite = NULL;
            if (map[x][y] == 0) {
                sprite = getSpriteImageByLevel(1);
                sprite->setPosition(Point(offsetX, offsetY));
                sprite->setTag(1);
                switch (height > width ? height : width) {
                    case 3:
                        sprite->setScale(scaleFactor - 0.1);
                        break;
                    case 4:
                        sprite->setScale(scaleFactor - 0.2);
                        break;
                    case 5:
                        sprite->setScale(scaleFactor - 0.3);
                        break;
                    default:
                        sprite->setScale(scaleFactor);
                        break;
                }
            }else{
                sprite = getSpriteImageByLevel(2);
                sprite->setTag(2);
                switch (height > width ? height : width) {
                    case 3:
                        sprite->setScale(scaleFactor - 0.1);
                        break;
                    case 4:
                        sprite->setScale(scaleFactor - 0.2);
                        break;
                    case 5:
                        sprite->setScale(scaleFactor - 0.3);
                        break;
                    default:
                        sprite->setScale(scaleFactor);
                        break;
                }

                sprite->setPosition(Point(offsetX, offsetY));
                
            }
            
            if (currentRound > 1) {
                randRotate = arc4random()%(width*height);
                if (randRotate == height) {
                    if (arc4random()%2 == 0) {
                        sprite->setRotation(90);
                    }else
                        sprite->setRotation(180);
                }
            }else
                if (currentRound > 2) {
                    randRotate = arc4random()%height + 1;
                    if (randRotate == height) {
                        sprite->setRotation(arc4random()%180);
                    }
                }
            pics->addObject(sprite);
            gridNode->addChild(sprite, 0);
            
            offsetY = offsetY + imageSizeHeight;
        }
        offsetX = offsetX + imageSizeWidth;
        offsetY = offsetRoot.y;
    }
    
}
void HelloWorld::resetMap()
{
    for (int i = 0; i< width; i++) {
        for (int j = 0; j < height; j++) {
            map[i][j] = 0;
        }
    }
    int offsetX = arc4random()%width ;
    int offsetY = arc4random()%height ;
    log("offX = %d, offY = %d", offsetX, offsetY);
    map[offsetX][offsetY] = 1;
}

void HelloWorld::resetNewGame()
{
    this->removeChild(gridNode, true);
    gridNode = NULL;
    pics->removeAllObjects();
    
    width = 2;
    height = 2;
    if (gameState == FINISH) {
        gameScore = 0;
        currentLevel = 1;
        gameState = RUNNING;
        currentRound = 1;
        GameHUD::shareInstance()->updateScore(0);
        GameHUD::shareInstance()->updateLevel(1);
    }

    tmpLevel = 0;
    isTouchRight = false;
    imageSizeHeight = imageSizeWidth = IMAGE_SIZE_HEIGHT_MAX;
    this->resetMap();
    GameHUD::shareInstance()->setMaxTime(getTimePlayByRound(currentRound));
    GameHUD::shareInstance()->setTime(getTimePlayByRound(currentRound));
}

int HelloWorld::getTimePlayByRound(int round)
{
    switch (round) {
        case 1:
            return 100;
        case 2:
            return 70;
        case 3:
            return 50;
        default:
            return 40;
            break;
    }
}
Sprite* HelloWorld::getSpriteImageByLevel(int type)
{
    if (tmpLevel == 0) {
        tmpLevel = arc4random()%4+1;
    }
    
    Sprite* sprite = NULL;
    int rand = 1;
    if (currentLevel < 5) {
        rand = tmpLevel;
    }else
    if (currentLevel < 15) {
        rand = arc4random() % 2 + 1;
    }else
    if (currentLevel < 20) {
        rand = arc4random() % 4 + 2;
    }else
    if( currentLevel < 30){
        rand = arc4random() % 4 + 1;
    }else
        rand = arc4random()% 5 + 1;
    log("current level = %d , random = %d", currentLevel, rand);
    switch (type) {
        case 1:
            sprite = Sprite::create(String::createWithFormat("sad%d.png", rand)->getCString());
            break;
        case 2:
            sprite = Sprite::create(String::createWithFormat("smile%d.png", rand)->getCString());
            break;
        default:
            break;
    }
    return sprite;
}
void HelloWorld::updateTimer(float dt)
{
    if (!isTouchRight) {
        GameHUD::shareInstance()->updateTimerBar(2);
    }
    if (GameHUD::shareInstance()->getTime() <= 0) {
        // time out
        log("tim out");
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/game_over.mp3");
        gameState = FINISH;
        btnReplay->setEnabled(false);
        unscheduleAllSelectors();

        /* set hight score*/
        UserDefault* def = UserDefault::getInstance();
        int currentHscore = def->getIntegerForKey("HIGH_SCORE", 0);
        if (gameScore > currentHscore) {
            def->setIntegerForKey("HIGH_SCORE", gameScore);
            def->flush();
        }
        
        /**effect for right image */
        Object* child= NULL;
        CCARRAY_FOREACH(pics, child){
            Sprite* sprite = (Sprite*)child;
            if (sprite->getTag() == 2) {
                sprite->setAnchorPoint(Point(0.5f, 0.5f));
                FiniteTimeAction* scaleUpAction = ScaleTo::create(1.0f, 1.2);
                FiniteTimeAction* scaleDownAction = ScaleTo::create(1.0f, 0.5);
                sprite->runAction(Repeat::create(Sequence::create(scaleUpAction, scaleDownAction, NULL), 2.0f));
                break;
            }
        }
        schedule(schedule_selector(HelloWorld::endGame), 1.0f, 0, 3.0f);
    }
}

void HelloWorld::endGame(float dt)
{
    stopAllActions();
    auto resultLayer = ViewResult::create();
    this->addChild(resultLayer, 5);
}
void HelloWorld::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    if (gameState != FINISH && !isTouchRight) {
        log("touched");
        Touch* touch = touches[0];
        Point location = touch->getLocation();
        Object* child= NULL;
        CCARRAY_FOREACH(pics, child){
            Sprite* sprite = (Sprite*)child;
            if (sprite->getTag() == 2) {
                Rect spRect = sprite->getBoundingBox();
                if (spRect.containsPoint(location)) {
                    isTouchRight = true;
                    log("right!");
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/yes.mp3");
                    if (GameHUD::shareInstance()->getTime() > GameHUD::shareInstance()->getMaxTime() * 2/3) {
                        gameScore += 3;
                    }else
                        if (GameHUD::shareInstance()->getTime() > GameHUD::shareInstance()->getMaxTime()/3) {
                            gameScore += 2;
                        }else
                            gameScore += 1;
                    GameHUD::shareInstance()->updateScore(gameScore);
                    FiniteTimeAction* actionMoveDone = CallFuncN::create( CC_CALLBACK_1(HelloWorld::spriteMoveFinish, this));
                    
                    switch (arc4random()%4) {
                        case 0:
                        {
                            auto effects = ShuffleTiles::create(0.7, Size(15, 15), 10);
                            gridNode->runAction(Sequence::create(effects, actionMoveDone, NULL));
                            break;
                        }
                        case 1:
                        {
                            auto effects = FadeOutDownTiles::create(0.6, Size(16,12));
                            gridNode->runAction(Sequence::create(effects, actionMoveDone, NULL));
                            break;
                        }
                        case 2:
                        {
                            auto effects = TurnOffTiles::create(0.5, Size(48,32), 25);
                            gridNode->runAction(Sequence::create(effects, actionMoveDone, NULL));
                            break;
                        }
                        case 3:
                        {
                            auto effects =  SplitCols::create(0.5, 9);
                            gridNode->runAction(Sequence::create(effects, actionMoveDone, NULL));
                            break;
                        }
                            
                    }
                    
                    
                    break;
                }else{
                    log("Wrong!");
                    GameHUD::shareInstance()->updateTimerBar(GameHUD::shareInstance()->getTime()/3);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/no.mp3");
                }
                
            }
        }
        

    }
    
}

void HelloWorld::spriteMoveFinish(cocos2d::Node *node)
{ 
    this->removeChild(gridNode, true);
    gridNode = NULL;
    pics->removeAllObjects();
    this->getNextLevel();
    
}
void HelloWorld::onButtonExitClick(cocos2d::Object *sender)
{
    /**end game **/
    GameHUD::shareInstance()->updateTimerBar(100);
}
void HelloWorld::onButtonReplayClick(cocos2d::Object *sender)
{
    gameState = FINISH;
    this->resetNewGame();
    this->drawMap();
    
    schedule(schedule_selector(HelloWorld::updateTimer), 0.1f);
}


