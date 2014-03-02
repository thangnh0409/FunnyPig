#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
private:
    cocos2d::Size visibleSize;
    /*
     array for save map value
     **/
    int map[50][50];
    /*
     save width map
     **/
    int width;
    /*
     save height map
     **/
    int height;
    
    /*
     offset root for draw image
     **/
    cocos2d::Point offsetRoot;
    /*
     variable for retain width and height map
     **/
    int retain;
    
    /*
     current level game, init  = 1
     **/
    int currentLevel;
    
    /*
     array for sprite
     **/
    cocos2d::Array* pics;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    
    void getNextLevel(cocos2d::Node* node);
    
    /*
     draw texture map in layer
     **/
    void drawMap();
    
    void resetMap();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
