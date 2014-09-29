//
//  GameLayer.h
//  mySnake
//
//  Created by lifei zhen on 14-5-7.
//
//

#ifndef __mySnake__GameLayer__
#define __mySnake__GameLayer__

#include <iostream>
#include "cocos2d.h"

enum DIR_DEF
{
    UP = 1,
    DOWN,
    LEFT,
    RIGHT
};

class SnakeNode : public cocos2d::Ref{
public:
    DIR_DEF dir;
    int row,col;
};

class GameLayer : public cocos2d::Layer{
private:
    SnakeNode* s_Head;
    SnakeNode* s_Food;
    cocos2d::Vector<SnakeNode*> s_Body;
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    virtual void draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated);
    
    void update(float dt);
    
    void snakeDie();
    
    void menuBackToMain(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GameLayer);
    
    virtual bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    
};

#endif /* defined(__mySnake__GameLayer__) */
