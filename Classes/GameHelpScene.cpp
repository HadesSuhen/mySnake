//
//  GameHelpScene.cpp
//  mySnake
//
//  Created by lifei zhen on 14-5-7.
//
//

#include "GameHelpScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* GameHelp::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameHelp::create();
    
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool GameHelp::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto labelHelp = Label::create("Please click screen to start the game",
                                   "宋体", 24);
    labelHelp->setPosition(Point(480,320));
    this->addChild(labelHelp);
    
    auto labelBack = Label::create("MainMenu","宋体",24);
    auto uiBack = MenuItemLabel::create(labelBack, CC_CALLBACK_1(GameHelp::menuBackToMain, this));
    uiBack->setPosition(Point(100,50));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(uiBack, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}


void GameHelp::menuBackToMain(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}
