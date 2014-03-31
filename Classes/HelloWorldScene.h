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
     value of image height
     **/
    int imageSizeHeight;
    
    /*
     value of image width
     **/
    int imageSizeWidth;
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
     current round game, init  = 1
     **/
    int currentRound;
    /*
     state of game
     @values: RUNNING; FINISH; 
     **/
    int gameState;
    
    /*
     game score
     **/
    int gameScore;
    /*
     Bien danh dau de tranh touch dung 2 lan 
     **/
    bool isTouchRight;
    
    int tmpLevel;
    
    float scaleFactor;
    
    cocos2d::Sprite* background;
    
    cocos2d::Menu* btnReplay;
    /*
     array for sprite
     **/
    cocos2d::Array* pics;
    
    cocos2d::NodeGrid* gridNode;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    //virtual bool keyBackClick(void);
    
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    
    void getNextLevel();
    
    void getNextRound();
    
    void spriteMoveFinish(cocos2d::Node* node);
    /*
     draw texture map in layer
     **/
    void drawMap();
    
    void resetMap();
    
    void resetNewGame();
    
    int getTimePlayByRound(int round);
    /*
     get random texture
     @param: type: = 1 if sad image, type =2 if smile image
     **/
    cocos2d::Sprite* getSpriteImageByLevel(int type);
    
    
    void updateTimer(float dt);
    
    void endGame(float dt);
    
    void onButtonReplayClick(Object* sender);
    void onButtonExitClick(Object* sender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
