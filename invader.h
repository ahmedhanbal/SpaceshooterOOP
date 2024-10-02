#ifndef INVADER_H
#define INVADER_H

#include "enemy.h"

class Invader : public Enemy
{
public:
    Invader() : Enemy("img/invader.png") //def const
    {
        speed = 0.15;
        health=0;
        ammo = 1;
        enemySprite.setPosition(rand() % (int)(780 - enemySprite.getGlobalBounds().width), 0); //position
        x = enemySprite.getPosition().x;
        y = enemySprite.getPosition().y;
    }
 
    void fire(Bomb ***bombsArr, int &bombsize) override //firing
    {
        Bomb **newBombArr = new Bomb *[++bombsize];
        for (int i = 0; i < bombsize - 1; i++)
        {
            newBombArr[i] = (*bombsArr)[i];
        }
        newBombArr[bombsize - 1] = new Bomb("img/laser.png");
        newBombArr[bombsize - 1]->Position(enemySprite);
        delete[] *bombsArr;
        *bombsArr = newBombArr;
        ammo--;
    }

    void move(Sprite & player) override //moving
    {
        enemySprite.move(0, speed);
        x = enemySprite.getPosition().x;
        y = enemySprite.getPosition().y;
    }

    bool isOutOfBounds() override // if out of screen
    {
        return (y >= 780);
    }
};

#endif
