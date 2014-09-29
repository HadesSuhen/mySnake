//
//  GameHelpScene.h
//  mySnake
//
//  Created by lifei zhen on 14-5-7.
//
//

#ifndef __mySnake__GameHelpScene__
#define __mySnake__GameHelpScene__

#include <iostream>
#include "cocos2d.h"
class GameHelp : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuBackToMain(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GameHelp);
    
};

#endif /* defined(__mySnake__GameHelpScene__) */
