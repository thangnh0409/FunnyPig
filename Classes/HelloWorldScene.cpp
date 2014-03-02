#include "HelloWorldScene.h"

#define DEFAULT_RETAIN      3
#define IMAGE_SIZE_WIDTH    70
#define IMAGE_SIZE_HEIGHT   70


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

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
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    /**
     init map
     **/

    width = 2;
    height = 2;
    retain = DEFAULT_RETAIN;
    for (int i = 0; i< 50; i++) {
        for (int j= 0; j<50; j++) {
            map[i][j] = 0;
        }
    }
    /* end init map */
    currentLevel = 0;
    pics = new Array;
    pics->initWithCapacity(100);
    this->resetMap();
    this->drawMap();
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    
    return true;
}

void HelloWorld::getNextLevel(Node* node)
{
    if (retain > 0) {
        if (width != height) {
            width++;
        }else
            retain--;
    }else{
        retain = DEFAULT_RETAIN;
        height++;
    }
    currentLevel ++;
    this->resetMap();
    this->drawMap();
    
    log("x= %d, y= %d", width, height);
}

void HelloWorld::drawMap()
{
    /* remove all objects in pics array and layer before draw new map */
    Object* child = NULL;
    CCARRAY_FOREACH(pics, child)
    {
        auto target = dynamic_cast<Sprite*>(child);
        pics->removeObject(target);
        //this->removeChild(target, true);
        log("remove child");
    }
    this->removeAllChildrenWithCleanup(true);

    
    offsetRoot = Point(visibleSize.width/2, visibleSize.height/2) - Point(width * IMAGE_SIZE_WIDTH /2 , height* IMAGE_SIZE_HEIGHT/2);
    int offsetX = offsetRoot.x;
    int offsetY = offsetRoot.y;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (map[x][y] == 0) {
                auto sprite = Sprite::create("sad1.png");
                sprite->setAnchorPoint(Point::ZERO);
                sprite->setPosition(Point(offsetX, offsetY));
                sprite->setTag(1);
                pics->addObject(sprite);
                this->addChild(sprite);
                //log("add object");
                
            }else{
                auto sprite = Sprite::create("smile1.png");
                sprite->setAnchorPoint(Point::ZERO);
                sprite->setTag(2);
                sprite->setPosition(Point(offsetX, offsetY));
                pics->addObject(sprite);
                this->addChild(sprite);
                // log("add object");
            }
            offsetY = offsetY + IMAGE_SIZE_HEIGHT;
        }
        offsetX = offsetX + IMAGE_SIZE_WIDTH;
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
void HelloWorld::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    Touch* touch = touches[0];
	Point location = touch->getLocation();
    Object* child= NULL;
    CCARRAY_FOREACH(pics, child){
        Sprite* sprite = (Sprite*)child;
        if (sprite->getTag() == 2) {
            Rect spRect = sprite->getBoundingBox();
            if (spRect.containsPoint(location)) {
                log("right!");
                Object* child1 = NULL;
                for (int i = 0; i < pics->count(); i++) {
                    log("run action");
                    child1 = pics->getObjectAtIndex(i);
                    Sprite* sp = dynamic_cast<Sprite*>(child1);
                    if (sp) {
                        FiniteTimeAction* actionMove = MoveTo::create(0.4, Point(0 , sp->getPositionY()));
                        FiniteTimeAction* actionMoveDone = CallFuncN::create( CC_CALLBACK_1(HelloWorld::getNextLevel, this));
                        if (i == pics->count() - 1) {
                            sp->runAction(Sequence::create( actionMove, actionMoveDone , NULL));
                        }else{
                            
                            sp->runAction(actionMove);
                        }

                    }
                }

                break;
            }else
                log("Wrong!");
        }
    }
    

    
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
