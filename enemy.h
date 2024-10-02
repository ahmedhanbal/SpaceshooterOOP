#ifndef ENEMY_H
#define ENEMY_H


#include "bomb.h"
class Enemy
{
public:
    Texture enemyTexture;
    Sprite enemySprite;
    float speed; //speed
    int x, y; //x and y pos
    int health; // health of enemy
    int ammo; // ammo quantiy of enemy

    Enemy(std::string png_path)
    {
        enemyTexture.loadFromFile(png_path);
        enemySprite.setTexture(enemyTexture);
        speed = 0.1;
        x = 0;
        y = 0;
    }
    Boundary getBoundary() // returns boundary vals
	{
		Boundary temp;
		return temp.getBoundaries(enemySprite);
	}

    virtual void fire(Bomb ***bombArr, int &bombsize) = 0;
    virtual void move(Sprite & player) = 0;
    virtual bool isOutOfBounds() = 0;
};

#endif
