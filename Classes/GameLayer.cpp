//
//  GameLayer.cpp
//  mySnake
//
//  Created by lifei zhen on 14-5-7.
//
//

#include "GameLayer.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }//<span style="font-family: Menlo;"> </span>
    
    auto labelBack = Label::create("MainMenu", "fonts/Marker Felt.ttf", 40);
    auto uiBack = MenuItemLabel::create(labelBack, CC_CALLBACK_1(GameLayer::menuBackToMain, this));
    uiBack->setPosition(Point(900,200));
    
    auto menu = Menu::create(uiBack, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    s_Head = new SnakeNode();
    s_Head->row = arc4random()%10;
    s_Head->col = arc4random()%10;
    
    s_Food = new SnakeNode();
    s_Food->row = arc4random()%10;
    s_Food->col = arc4random()%10;
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    this->schedule(schedule_selector(GameLayer::update), 0.5);
    
    return true;
}

void GameLayer::draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    //绘制直线
    glLineWidth(4);
    for (int i = 0; i < 11; i++) {
        DrawPrimitives::drawLine(Point(0,i*64), Point(640, i*64));
        DrawPrimitives::drawLine(Point(i*64,0), Point(i*64,640));
    }
    //绘制蛇头
    DrawPrimitives::drawSolidRect(Point(s_Head->col * 64, s_Head->row * 64),
                                  Point(s_Head->col * 64 + 64, s_Head->row * 64 + 64),
                                  Color4F(1.0f, 0, 0, 1.0f));
    //绘制食物
    DrawPrimitives::drawSolidRect(Point(s_Food->col * 64,s_Food->row * 64),
                                  Point(s_Food->col * 64 + 64,s_Food->row * 64 + 64),
                                  Color4F(0,0,1.0f,1.0f));
    //绘制蛇身
    for (auto &sn : s_Body) {
        DrawPrimitives::drawSolidRect(Point(sn->col * 64,sn->row * 64),
                                      Point(sn->col * 64 + 64,sn->row * 64 +64),
                                      Color4F(0, 0, 1.0f, 1.0f));
    }
    Layer::draw(renderer, transform, transformUpdated);
}

void GameLayer::update(float dt)
{
    //蛇身每一段跟随前一段移动
    for (int i = s_Body.size()-1; i >= 0; i--) {
        SnakeNode* sn = s_Body.at(i);
        if (i!=0) {
            SnakeNode* pre = s_Body.at(i-1);
            sn->row = pre->row;
            sn->col = pre->col;
            sn->dir = pre->dir;
        }else{
            sn->row = s_Head->row;
            sn->col = s_Head->col;
            sn->dir = s_Head->dir;
        }
    }
    
    //根据方向让蛇头移动
    switch (s_Head->dir) {
        case UP:
            s_Head->row++;
            if (s_Head->row >= 10) {
                s_Head->row = 0;
            }
            break;
        case DOWN:
            s_Head->row--;
            if (s_Head->row < 0) {
                s_Head->row = 9;
            }
            break;
        case LEFT:
            s_Head->col--;
            if (s_Head->col < 0) {
                s_Head->col = 9;
            }
            break;
        case RIGHT:
            s_Head->col++;
            if (s_Head->col >= 10) {
                s_Head->col = 0;
            }
            break;
        default:
            break;
    }
    //与食物碰撞检测
    if (s_Head->row == s_Food->row && s_Head->col == s_Food->col) {
        s_Food->row = arc4random()%10;
        s_Food->col = arc4random()%10;
        
        SnakeNode* sn = new SnakeNode();
        SnakeNode* last = NULL;
        
        if (s_Body.size() > 0) {
            last = s_Body.back();
        }else{
            last = s_Head;
        }
        
        switch (last->dir) {
            case UP:
                sn->row = last->row - 1;
                sn->col = last->col;
                break;
            case DOWN:
                sn->row = last->row + 1;
                sn->col = last->col;
                break;
            case LEFT:
                sn->row = last->row;
                sn->col = last->col + 1;
                break;
            case RIGHT:
                sn->row = last->row;
                sn->col = last->col - 1;
                break;
                
            default:
                break;
        }
        //将食物加入身体
        s_Body.pushBack(sn);
    }
    
    for (int j=1; j<s_Body.size(); j++) {
        if (s_Head->row == s_Body.at(j)->row && s_Head->col == s_Body.at(j)->col) {
            GameLayer::snakeDie();
        }
    }
}

void GameLayer::snakeDie()
{
    this->unscheduleAllSelectors();
    auto title = Label::create("Game Over","fonts/Marker Felt.ttf",50);
    title->setAnchorPoint(Point::ANCHOR_MIDDLE);
    title->setPosition(575,520);
    title->enableShadow(Color4B::RED);
    this->addChild(title);
    
    auto restartLabel = Label::create("Restart","fonts/Marker Felt.ttf",40);
    restartLabel->enableShadow(Color4B::GREEN);
    auto restartMenu = MenuItemLabel::create(restartLabel,[](Ref*){Director::getInstance()->replaceScene(GameLayer::createScene()); });
    restartMenu->setPosition(Point(-200,0));
    auto backLabel = Label::create("MainMenu", "fonts/Marker Felt.ttf", 40);
    backLabel->enableShadow(Color4B::GREEN);
    auto backMenu = MenuItemLabel::create(backLabel, CC_CALLBACK_1(GameLayer::menuBackToMain, this));
    backMenu->setPosition(Point(200, 0));
    auto menu = Menu::create(restartMenu,backMenu,NULL);
    this->addChild(menu);
}


void GameLayer::menuBackToMain(cocos2d::Ref *pSender)
{
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Point tPos = touch->getLocation();
    int tRow = ((int)tPos.y)/64;
    int tCol = ((int)tPos.x)/64;
    
    if (abs(tRow - s_Head->row) > abs(tCol - s_Head->col)) {
        if (tRow > s_Head->row) {
            s_Head->dir = UP;
        }else{
            s_Head->dir = DOWN;
        }
    }
    else
    {
        if (tCol > s_Head->col) {
            s_Head->dir = RIGHT;
        }else{
            s_Head->dir = LEFT;
        }
    }
    return true;
}
