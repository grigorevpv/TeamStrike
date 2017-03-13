//
// Created by pavel on 10.03.17.
//

#include <iostream>
#include "Level1Scene.h"
#include "PauseScene.h"
#include "Warrior.h"

USING_NS_CC;

Scene *Level1Scene::createScene() {
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0,0));
    auto layer = Level1Scene::create();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSSHAPE_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);


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

    _sprRobot = Warrior::create();
    this->addChild(_sprRobot, 1);

    auto bg = Sprite::create("space_1.jpg");
    bg->setAnchorPoint(Vec2( ));
    bg->setPosition(0, 0);
    this->addChild(bg ,-1);

    auto sprMeteor = Sprite::create("meteor.png");
    sprMeteor->setPosition(visibleSize.width/2, visibleSize.height * 0.8f);
    auto meteorBody = PhysicsBody::createCircle( sprMeteor->getContentSize().height , PhysicsMaterial(0, 1, 0) );
    sprMeteor->setPhysicsBody( meteorBody );
    this->addChild(sprMeteor, 0);

    //Animation
    Vector<SpriteFrame*> frames;
    Size meteorSize = sprMeteor->getContentSize();
    frames.pushBack(SpriteFrame::create("meteor.png", Rect(0, 0, meteorSize.width, meteorSize.height)));
    frames.pushBack(SpriteFrame::create("meteor.png", Rect(0, 0, meteorSize.width, meteorSize.height)));
    auto animation = Animation::createWithSpriteFrames(frames, 0.8f);
    auto animate = Animate::create(animation);
    sprMeteor->runAction(RepeatForever::create(animate));
    setPhysicsBody(_sprRobot);
    setPhysicsBody(sprMeteor);
    initPhisics();

    _sprRobot->getPhysicsBody()->setVelocity(Vect(0, -25));
    sprMeteor->getPhysicsBody()->setVelocity(Vect(0, -25));


        auto listener = EventListenerKeyboard::create();
        listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event) {
            switch (keyCode) {
                case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                case cocos2d::EventKeyboard::KeyCode::KEY_A:

                    getWarrior()->MoveWarrior(Vec2(-10.0f, .0f));
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                case cocos2d::EventKeyboard::KeyCode::KEY_D:
                    getWarrior()->MoveWarrior(Vec2(10.0f, .0f));
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
                case cocos2d::EventKeyboard::KeyCode::KEY_W:
                    std::cout << "press up" << std::endl;
                    getWarrior()->getPhysicsBody()->applyImpulse(Vect(100, 0));
                    getWarrior()->MoveWarrior(Vec2(.0f, +10.0f));
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                case cocos2d::EventKeyboard::KeyCode::KEY_S:
                    std::cout << "press down" << std::endl;
                    getWarrior()->MoveWarrior(Vec2(.0f, -10.0f));
                    break;
            }
        };
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _sprRobot);


        listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
        {

            switch (keyCode)
            {
                // GetPlayerPlane() Movement
                case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
                    break;

                case cocos2d::EventKeyboard::KeyCode::KEY_A:
                    getWarrior()->MoveWarrior(Vec2(1.0f, .0f));
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_D:
                    getWarrior()->MoveWarrior(Vec2(-1.0f, .0f));

                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_W:
                    getWarrior()->MoveWarrior(Vec2(.0f, -1.0f));
                    break;
                case cocos2d::EventKeyboard::KeyCode::KEY_S:
                    getWarrior()->MoveWarrior(Vec2(.0f, 1.0f));
                    break;

                default:
                    break;
            }
        };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _sprRobot);

    this->scheduleUpdate();


    return true;
}

void Level1Scene::pauseCallback(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionSplitCols::create(1.0, PauseScene::createScene()));
}

void Level1Scene::setPhysicsBody(cocos2d::Sprite *sprite) {
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width/2);
    body->setContactTestBitmask(true);
    body->setDynamic(true);
    sprite->setPhysicsBody(body);
}

bool Level1Scene::onCollision(cocos2d::PhysicsContact& contact) {
    //_sprRobot->getPhysicsBody()->setVelocity(Vect());
    auto body = _sprRobot->getPhysicsBody();
    body->setVelocity(Vect());
    body->applyTorque(100000);
    CCLOG("Collision detected!");
//    _sprRobot->setVisible(false);
    return false;
}

void Level1Scene::initPhisics() {
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Level1Scene::onCollision, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

Warrior *Level1Scene::getWarrior() {
    return _sprRobot;
}



