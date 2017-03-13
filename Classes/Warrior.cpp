//
// Created by pavel on 13.03.17.
//

#include <iostream>
#include "Warrior.h"

namespace
{
    const int DefaultWarriorHP = 100;
    const float DefaultWarriorMaxSpeed = 100.0f;
}


Warrior::Warrior() {}
Warrior::~Warrior() {}

Warrior *Warrior::create() {
    Warrior* pSprite = new Warrior();
        pSprite->initWithFile("robot_little.png");
        pSprite->InitOptions();
        pSprite->AddEvents();
        return pSprite;
}

void Warrior::InitOptions() {
    auto warrior_body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0,0,0));
    warrior_body->setCollisionBitmask(1);
    warrior_body->setContactTestBitmask(true);
    warrior_body->setDynamic(true);
    this->setPhysicsBody(warrior_body);
    this->setScale(0.75);
    //this->setPosition(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2 + this->getContentSize().height/2);
    //this->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 8));
    this->setPosition(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2);
    _baseHP = DefaultWarriorHP;
    _currentHP = _baseHP;
    _movementDirection = Vec2(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2);
}

int Warrior::GetCurrentHP() {
    return _currentHP;
}

bool Warrior::MoveWarrior(const Vec2 direction) {
    _movementDirection = this->_position;
    _movementDirection += direction;
    this->setPosition(_movementDirection);
    return true;
}

bool Warrior::StopWarrior() {
    _movementDirection = Vec2();
    return true;
}

void Warrior::AddEvents() {
    scheduleUpdate();
}



