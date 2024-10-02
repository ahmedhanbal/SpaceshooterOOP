#ifndef BULLET_H
#define BULLET_H
#include "boundaries.h"
#include <math.h>
class Bullet 
{
public:
    Texture bulltex,bullet_45,bullet_135,bullet_a135,bullet_a45; // rotated bullet textures
    Sprite bullet;
    float speed = 0.5;
    float angle;
    int x_ax, y_ax;
    
    Bullet() 
    {
        bulltex.loadFromFile("img/bullet.png");
        bullet_45.loadFromFile("img/bullet_45.png");
        bullet_135.loadFromFile("img/bullet_135.png");
        bullet_a45.loadFromFile("img/bullet_a45.png");
        bullet_a135.loadFromFile("img/bullet_a135.png");
        bullet.setTexture(bulltex);
        bullet.setScale(1,0.5);
    }
    
    void Position(const Sprite &player, float rotationAngle) // position fn, sets rotat of bullet as well
    {
        x_ax = player.getPosition().x;
        y_ax = player.getPosition().y;
        bullet.setPosition(x_ax + player.getGlobalBounds().width / 2, y_ax - player.getGlobalBounds().height / 2);
        angle=rotationAngle;
    }
    
    void moveBullet() // moves bulelt whilst keeping its rotated texture
    {
        // Calculate the movement in the x and y directions based on the rotation angle
        float deltaX = -speed * std::sin(angle * 3.14159 / 180.0);
        float deltaY = -speed * std::cos(angle * 3.14159 / 180.0);
        if(angle==45) bullet.setTexture(bullet_45);
        else if(angle==135) bullet.setTexture(bullet_135);
        else if(angle==-45) bullet.setTexture(bullet_a45);
        else if(angle==-135) bullet.setTexture(bullet_a135);
        bullet.move(deltaX, deltaY);
        x_ax = bullet.getPosition().x;
        y_ax = bullet.getPosition().y;
    }
    Boundary getBoundary() // boundary vals of bullet
	{
		Boundary temp;
		return temp.getBoundaries(bullet);
	}
};
#endif