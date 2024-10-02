#ifndef DRAGON_H
#define DRAGON_H

#include "enemy.h"

class Dragon : public Enemy
{
public:
    Dragon() : Enemy("img/dragon.png") //def const
    {
        speed = 0.03;
        ammo=3;
        health = 3;
        enemySprite.setPosition(rand() % (int)(780 - enemySprite.getGlobalBounds().width), 0); // position
        x = enemySprite.getPosition().x;
        y = enemySprite.getPosition().y;
    }

    void fire(Bomb ***bombsArr, int &bombsize) override //firing array
    {
        Bomb **newBombArr = new Bomb *[++bombsize];
        for (int i = 0; i < bombsize - 1; i++)
        {
            newBombArr[i] = (*bombsArr)[i];
        }
        newBombArr[bombsize - 1] = new Bomb("img/dr_bomb.png");
        newBombArr[bombsize - 1]->Position(enemySprite);
        delete[] *bombsArr;
        *bombsArr = newBombArr;
        ammo--;
    }

    void move(Sprite & player) override // move fn
    {
        enemySprite.move(0,0.1);
        x = enemySprite.getPosition().x;
        y = enemySprite.getPosition().y;
    }

    bool isOutOfBounds() override // if out of screen
    {
        return (y >= 780);
    }
};

#endif
