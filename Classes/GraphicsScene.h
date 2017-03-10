//
// Created by pavel on 09.03.17.
//

#ifndef MYGAME_GRAPHICSSCENE_H
#define MYGAME_GRAPHICSSCENE_H

#include "cocos2d.h"

class GraphicsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void pauseCallback(cocos2d::Ref* pSender);
    void startGame(cocos2d::Ref* pSender);
    CREATE_FUNC(GraphicsScene);
};


#endif //MYGAME_GRAPHICSSCENE_H
