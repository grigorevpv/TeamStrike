//
// Created by pavel on 10.03.17.
//

#ifndef MYGAME_PAUSESCENE_H
#define MYGAME_PAUSESCENE_H


//#include <2d/CCLayer.h>
#include "cocos2d.h"

class PauseScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void exitPause(cocos2d::Ref* pSender);
    CREATE_FUNC(PauseScene);
private:
    cocos2d::Director *_director;
    cocos2d::Size _visibleSize;

};


#endif //MYGAME_PAUSESCENE_H
