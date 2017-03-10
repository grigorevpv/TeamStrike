//
// Created by pavel on 10.03.17.
//

#include "PauseScene.h"

USING_NS_CC;

cocos2d::Scene *PauseScene::createScene() {
    auto scene = Scene::create();
    auto layer = PauseScene::create();
    scene->addChild(layer);
    return scene;
}

bool PauseScene::init() {

    if (!Layer::init()){
        return false;
    }
    _director = Director::getInstance();
    _visibleSize = _director->getVisibleSize();
    Vec2 origin = _director->getVisibleOrigin();
    auto pauseItem = MenuItemImage::create("play_little.png", "play_little.png", CC_CALLBACK_1(PauseScene::exitPause, this));
    pauseItem->setPosition(Vec2(origin.x + _visibleSize.width - pauseItem->getContentSize().width/2, origin.y + pauseItem->getContentSize().height/2));

    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("PAUSE", "fonts/Marker Felt.ttf", 96);
    label->setPosition(origin.x + _visibleSize.width/2 , origin.y + _visibleSize.height/2);
    this->addChild(label, 1);
    return true;
}

void PauseScene::exitPause(cocos2d::Ref *pSender) {
    Director::getInstance()->popScene();
}
