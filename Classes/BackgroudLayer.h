//
//  BackgroudLayer.h
//  HelloCpp
//
//  Created by belm on 13-10-16.
//
//

#ifndef __HelloCpp__BackgroudLayer__
#define __HelloCpp__BackgroudLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class BackgroudLayer: public Layer{
public:
    BackgroudLayer();
    virtual ~BackgroudLayer();
    virtual bool init();
    CREATE_FUNC(BackgroudLayer);
    virtual void onEnter();
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    virtual void onTouchCancelled(Touch *touch, Event *event);
    virtual void update(float delta);
    
    void move(float dt);
    void bullet(float dt);
    void bulletMove(float dt);
    void enemy(float dt);
    void enemyMove(float dt);
public:
    Sprite *startSprite1;
    Sprite *startSprite2;
    Sprite *hero;
    Array *bulletArray;
    Array *enemyArray;
};

#endif /* defined(__HelloCpp__BackgroudLayer__) */
