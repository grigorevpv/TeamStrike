//
// Created by pavel on 13.03.17.
//

#ifndef MYGAME_WARRIOR_H
#define MYGAME_WARRIOR_H

#include "cocos2d.h"
USING_NS_CC;

class Warrior : public cocos2d::Sprite {
public:
    Warrior();
    ~Warrior();
    static Warrior* create();

    int GetCurrentHP();
    bool MoveWarrior(const Vec2 direction);
    bool StopWarrior();
    void AddEvents();
    void MakeBoom();
    void InitOptions();

protected:
    int _baseHP;
    int _currentHP;
    Vec2 _movementDirection;

};


#endif //MYGAME_WARRIOR_H
