#ifndef MONSTER_H
#define MONSTER_H

#include "enemy.h"

class Monster : public Enemy
{
public:
    Monster() : Enemy("img/monster.png") //default const
    {
        speed = 0.05;
        health = 2;
        ammo = 10;
        enemySprite.setPosition(rand() % (int)(780 - enemySprite.getGlobalBounds().width), 0);//setting default pos
        x = enemySprite.getPosition().x;
        y = enemySprite.getPosition().y;
    }

    void fire(Bomb ***bombsArr, int &bombsize) override //update and delete ammo
    {
        Bomb **newBombArr = new Bomb *[++bombsize];
        for (int i = 0; i < bombsize - 1; i++)
        {
            newBombArr[i] = (*bombsArr)[i];
        }
        newBombArr[bombsize - 1] = new Bomb("img/bomb.png");
        newBombArr[bombsize - 1]->Position(enemySprite);
        delete[] *bombsArr;
        *bombsArr = newBombArr;
        ammo--;
    }

    void move(Sprite & player) override //move 
    {
        enemySprite.move(0, speed);
        x = enemySprite.getPosition().x;
        y = enemySprite.getPosition().y;
    }

    bool isOutOfBounds() override
    {
        return (y >= 780);
    }
};

#endif
