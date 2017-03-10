//
// Created by pavel on 10.03.17.
//

#include "Level1Scene.h"
#include "PauseScene.h"

USING_NS_CC;

Scene *Level1Scene::createScene() {
    auto scene = Scene::create();
    auto layer = Level1Scene::create();
    scene->addChild(layer);

    return scene;
}

bool Level1Scene::init() {
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pauseseItem = MenuItemImage::create(
            "pause_little.png",
            "pause_little.png",
            CC_CALLBACK_1(Level1Scene::pauseCallback, this));

    pauseseItem->setPosition(Vec2(origin.x + visibleSize.width - pauseseItem->getContentSize().width/2 ,
                                  origin.y + pauseseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(pauseseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto sprite = Sprite::create("space_1.jpg");
    auto sprite_2 = Sprite::create("robot_little.png");
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite_2->setAnchorPoint(Vec2(0, 0));
    sprite->addChild(sprite_2, 0);
    sprite_2->setPosition(165, 187);
    this->addChild(sprite, 0);

    auto moveBy = MoveBy::create(0.5, Vec2(0, 250));
    sprite_2->runAction(moveBy);

    return true;
}

void Level1Scene::pauseCallback(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionSplitCols::create(1.0, PauseScene::createScene()));
}
