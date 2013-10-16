//
//  BackgroudLayer.cpp
//  HelloCpp
//
//  Created by belm on 13-10-16.
//
//

#include "BackgroudLayer.h"
#include "VisibleRect.h"

BackgroudLayer::BackgroudLayer()
{
    startSprite1 = NULL;
    startSprite2 = NULL;
    hero = NULL;
    bulletArray = new Array();
    bulletArray->init();
    enemyArray = new Array();
    enemyArray->init();
}

BackgroudLayer::~BackgroudLayer()
{
    CC_SAFE_RELEASE(bulletArray);
}

bool BackgroudLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    return true;
}

void BackgroudLayer::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
    // Register Touch Event
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(BackgroudLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(BackgroudLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(BackgroudLayer::onTouchEnded, this);
    
    EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, this);
    
    startSprite1 = Sprite::createWithSpriteFrameName("background_2.png");
    startSprite1->setAnchorPoint(Point(0, 0));
    startSprite1->setPosition(Point(0,0));
    this->addChild(startSprite1);
    
    startSprite2 = Sprite::createWithSpriteFrameName("background_2.png");
    startSprite2->setAnchorPoint(Point(0, 0));
    startSprite2->setPosition(Point(0,startSprite1->getContentSize().height-3));
    this->addChild(startSprite2);
    
    schedule(schedule_selector(BackgroudLayer::move), 0.001f);//更新背景
    
    hero = Sprite::createWithSpriteFrameName("hero_fly_1.png");
    hero->setPosition(Point(VisibleRect::bottom().x, VisibleRect::bottom().y+hero->getContentSize().height/2));
    this->addChild(hero);
    
    schedule(schedule_selector(BackgroudLayer::bullet), 0.1f);//产生子弹
    schedule(schedule_selector(BackgroudLayer::bulletMove), 1/60.f);//更新子弹
    
    schedule(schedule_selector(BackgroudLayer::enemy), 2.0f);//产生敌机
    schedule(schedule_selector(BackgroudLayer::enemyMove), 1/60.f);//更新敌机
}

void BackgroudLayer::move(float dt)
{
    startSprite1->setPositionY(startSprite1->getPositionY()-2);
    startSprite2->setPositionY(startSprite1->getPositionY()+startSprite1->getContentSize().height-3);
    if (startSprite2->getPositionY() <=0) {
        startSprite1->setPositionY(0);
    }
}

bool BackgroudLayer::onTouchBegan(Touch *touch, Event *event)
{
    Point point = touch->getLocation();
    hero->setPosition(point);
    return true;
}

void BackgroudLayer::onTouchMoved(Touch *touch, Event *event)
{
}

void BackgroudLayer::onTouchEnded(Touch *touch, Event *event)
{
}

void BackgroudLayer::onTouchCancelled(Touch *touch, Event *event)
{
}

void BackgroudLayer::bullet(float dt)
{
    //int randNum = rand()%2+1;
    //String *str = String::createWithFormat("bullet%d.png",randNum);
    auto bulletSprite = Sprite::createWithSpriteFrameName("bullet1.png");
    bulletSprite->setPosition(Point(hero->getPositionX(),hero->getPositionY()+hero->getContentSize().height/2));
    bulletArray->addObject(bulletSprite);
    this->addChild(bulletSprite);
}

void BackgroudLayer::bulletMove(float dt)
{
    if (bulletArray && bulletArray->count()) {
        Object *obj = NULL;
        CCARRAY_FOREACH(bulletArray, obj){
            auto bullet = (Sprite*)obj;
            bullet->setPositionY(bullet->getPositionY()+20);
            //移除不在可见区域的子弹
            if (bullet->getPositionY() > VisibleRect::top().y) {
                bulletArray->removeObject(bullet);
                bullet->removeFromParent();
            }
        }
    }
}

void BackgroudLayer::enemy(float dt)
{
    int randNum = rand()%4+1;
    String *str = String::createWithFormat("enemy%d_fly_1.png",randNum);
    auto sprite= Sprite::createWithSpriteFrameName(str->getCString());
    Size size = sprite->getContentSize();
    int randPos = rand()%(int)(VisibleRect::rightTop().x)+1;
    if (randPos < size.width/2) {
        randPos = size.width/2;
    }else if(randPos > VisibleRect::rightTop().x - size.width/2){
        randPos = VisibleRect::rightTop().x - size.width/2;
    }
    sprite->setPosition(Point(randPos,VisibleRect::top().y));
    enemyArray->addObject(sprite);
    this->addChild(sprite);
}

void BackgroudLayer::enemyMove(float dt)
{
    if (enemyArray && enemyArray->count()) {
        Object *obj = NULL;
        CCARRAY_FOREACH(enemyArray, obj){
            auto bullet = (Sprite*)obj;
            bullet->setPositionY(bullet->getPositionY()-5);
            //移除不在可见区域的子弹
            if (bullet->getPositionY() <= 0) {
                bulletArray->removeObject(bullet);
                bullet->removeFromParent();
            }
        }
    }
}

void BackgroudLayer::update(float delta)
{
    Object *obj = NULL;
    CCARRAY_FOREACH(enemyArray, obj){
        auto enemy = (Sprite*)obj;
        Rect rect = enemy->getBoundingBox();
        //检测与hero碰撞
        if (rect.containsPoint(hero->getPosition())) {
            enemyArray->removeObject(enemy);
            enemy->removeFromParent();
            break;
        }
        
        //检测与子弹碰撞
        Object *object = NULL;
        CCARRAY_FOREACH(bulletArray, object){
            auto bullet = (Sprite*)object;
            if(rect.containsPoint(bullet->getPosition())){
                bulletArray->removeObject(bullet);
                bullet->removeFromParent();
                
                enemyArray->removeObject(enemy);
                enemy->removeFromParent();
                break;
            }
        }
    }
}