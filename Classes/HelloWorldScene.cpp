#include "HelloWorldScene.h"
#include "VisibleRect.h"
#include "MainLayer.h"
USING_NS_CC;

HelloWorld::HelloWorld()
{
}

HelloWorld::~HelloWorld()
{
}

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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameArts-hd.plist");
    auto startSprite = Sprite::createWithSpriteFrameName("background_2.png");
    startSprite->setPosition(VisibleRect::center());
    this->addChild(startSprite);
    
    auto logoSprite = Sprite::create("BurstAircraftLogo-hd.png");
    logoSprite->setPosition(centerOf(startSprite));
    startSprite->addChild(logoSprite);
    return true;
}

void HelloWorld::onEnter()
{
    Director::getInstance()->replaceScene(MainLayer::scene());
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}