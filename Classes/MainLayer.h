//
//  MainLayer.h
//  HelloCpp
//
//  Created by belm on 13-10-16.
//
//

#ifndef __HelloCpp__MainLayer__
#define __HelloCpp__MainLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class MainLayer : Layer{
public:
    MainLayer(){};
    virtual ~MainLayer(){};
    virtual bool init();
    static Scene* scene();
    
    CREATE_FUNC(MainLayer);
};

#endif /* defined(__HelloCpp__MainLayer__) */
