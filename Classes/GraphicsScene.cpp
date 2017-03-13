//
// Created by pavel on 09.03.17.
//

#include "GraphicsScene.h"
#include "PauseScene.h"
#include "Level1Scene.h"

USING_NS_CC;

Scene* GraphicsScene::
createScene()
{
    auto scene = Scene::create();
    auto layer = GraphicsScene::create();
    scene->addChild(layer);

    return scene;
}

bool GraphicsScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//    auto pauseseItem = MenuItemImage::create(
//            "pause_little.png",
//            "pause_little.png",
//            CC_CALLBACK_1(GraphicsScene::pauseCallback, this));
//
//    pauseseItem->setPosition(Vec2(origin.x + visibleSize.width - pauseseItem->getContentSize().width/2 ,
//                                origin.y + pauseseItem->getContentSize().height/2));
    auto startGameItem = MenuItemImage::create(
            "start_buttom_little.png",
            "start_buttom_little.png",
            CC_CALLBACK_1(GraphicsScene::startGame, this));

    startGameItem->setPosition(Vec2(origin.x + visibleSize.width - startGameItem->getContentSize().width/2 ,
                                  origin.y + startGameItem->getContentSize().height/2));

    startGameItem->setPosition(Vec2(origin.x + visibleSize.width/2 ,
                                    origin.y + startGameItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(startGameItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("StrikeTime", "fonts/Marker Felt.ttf", 80);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    auto sprite = Sprite::create("space.jpg");
    auto sprite_2 = Sprite::create("robot_main.png");
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite_2->setAnchorPoint(Vec2(0, 0));
    sprite->addChild(sprite_2, 0);
    sprite_2->setPosition(165, 187);
    this->addChild(sprite, 0);

    return true;
}

void GraphicsScene::pauseCallback(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionSplitCols::create(1.0, PauseScene::createScene()));
}

void GraphicsScene::startGame(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionSplitCols::create(1.0, Level1Scene::createScene()));
}
