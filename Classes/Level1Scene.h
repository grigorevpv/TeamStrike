//
// Created by pavel on 10.03.17.
//

#ifndef MYGAME_LEVEL1SCENE_H
#define MYGAME_LEVEL1SCENE_H

#include "cocos2d.h"

class Level1Scene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void pauseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(Level1Scene);
};


#endif //MYGAME_LEVEL1SCENE_H
