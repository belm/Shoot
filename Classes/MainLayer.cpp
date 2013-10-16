//
//  MainLayer.cpp
//  HelloCpp
//
//  Created by belm on 13-10-16.
//
//

#include "MainLayer.h"
#include "BackgroudLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool MainLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    BackgroudLayer *backgroud = BackgroudLayer::create();
    backgroud->setPosition(0, 0);
    this->addChild(backgroud);
    //play music
    SimpleAudioEngine::getInstance()->playEffect("game_music.mp3",true);
    return true;
}

Scene* MainLayer::scene()
{
    auto scene = Scene::create();
    MainLayer *main = MainLayer::create();
    scene->addChild(main);
    return scene;
}