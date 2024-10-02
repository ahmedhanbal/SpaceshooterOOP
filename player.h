
#include "bullet.h"
#include <iostream>
class Player
{
public:
	Texture plyrTex, plyr_ru, plyr_rs, plyr_lu, plyr_ls; // player texture
	Sprite plyrite;										 // player sprite
	Bullet **bulletsArr;								 // a bullet ptr for dynamic array
	Text helth,kill;
	Font font;
	int bullsize;										 // stores total no of bullets
	float speed ;
	int x, y;
	float angle; // angle of rotat
	bool isRotated; // if rotated
	int health,kills; //health and kills of player
	Player(std::string png_path)
	{

		plyrTex.loadFromFile(png_path);
		// for rotated textures
		plyr_ls.loadFromFile("img/player_ls.png");
		plyr_lu.loadFromFile("img/player_lu.png");
		plyr_rs.loadFromFile("img/player_rs.png");
		plyr_ru.loadFromFile("img/player_ru.png");
		plyrite.setTexture(plyrTex);
		font.loadFromFile("font/UbuntuNerdFont-Bold.ttf");
		helth.setFont(font);
		helth.setCharacterSize(20);
		helth.setFillColor(Color::White);
		helth.setPosition(870,500);
		kill.setFont(font);
		kill.setCharacterSize(20);
		kill.setFillColor(Color::White);
		kill.setPosition(880,300);
		kills=0;
		x = 340;
		y = 700;
		health=100;
		plyrite.setPosition(sf::Vector2f(x, y));
		plyrite.setScale(0.75, 0.75);
		bulletsArr = nullptr;
		bullsize = 0;
		speed= 0.1;
		isRotated = false;
		angle=0;
	}
	Boundary getBoundary() //for boundary values of sprite
	{
		Boundary temp;
		return temp.getBoundaries(plyrite);
	}
	void fire() // for firing bullets
	{
		Bullet **newBulletArr = new Bullet *[++bullsize];
		for (int i = 0; i < bullsize - 1; i++)
		{
			newBulletArr[i] = bulletsArr[i];
		}
		newBulletArr[bullsize - 1] = new Bullet();
		newBulletArr[bullsize - 1]->Position(plyrite,angle);
		delete[] bulletsArr;
		bulletsArr = newBulletArr;
	}

	void bulletmove() // moving bullets
	{
		for (int i = 0; i < bullsize; i++)
		{
			bulletsArr[i]->moveBullet();
		}
	}
	void deleteBullet() // deleting bullets 
	{
		int counter = 0;
		for (int i = 0; i < bullsize; i++)
		{
			if (!(bulletsArr[i]->x_ax < 0 || bulletsArr[i]->x_ax > 780 || bulletsArr[i]->y_ax < 0 || bulletsArr[i]->y_ax > 780))
			{ // If the bullet is still on screen, // move it to the beginning of the array
				bulletsArr[counter] = bulletsArr[i];
				counter++;
			}
			else
			{ // If the bullet is off screen, delete it
				delete bulletsArr[i];
			}
		}
		bullsize = counter;
	}

	void moveAround() //implemets wrapAround features
	{
		if (plyrite.getPosition().x < 0)
		{
			if (isRotated)
				plyrite.setPosition(780 - plyrite.getGlobalBounds().width, 780 - plyrite.getPosition().y);
			else
				plyrite.setPosition(780 - plyrite.getGlobalBounds().width, plyrite.getPosition().y);
		}
		else if (plyrite.getPosition().x + plyrite.getGlobalBounds().width > 780)
		{
			if (isRotated)
				plyrite.setPosition(0, 780 - plyrite.getPosition().y);
			else
				plyrite.setPosition(0, plyrite.getPosition().y);
		}
		else if (plyrite.getPosition().y < 0)
		{
			if (isRotated)
				plyrite.setPosition(780 - plyrite.getPosition().x, 780 - plyrite.getGlobalBounds().height);
			else
				plyrite.setPosition(plyrite.getPosition().x, 780 - plyrite.getGlobalBounds().height);
		}
		else if (plyrite.getPosition().y > 780)
		{
			if (isRotated)
				plyrite.setPosition(780 - plyrite.getPosition().x, 1);
			else
				plyrite.setPosition(plyrite.getPosition().x, 1);
		}
	}
	void move(std::string s) // moves the player
	{
		float delta_x = 0, delta_y = 0; angle=0;
		isRotated = false; 
		if (s == "l") // left move
			delta_x = -1;
		else if (s == "r") // right move
			delta_x = 1;
		else if (s == "u") // up move
			delta_y = -1;
		else if (s == "d") // down move
			delta_y = 1;
		else if (s == "lu")
		{ // left upwards
			delta_y = 0.0717;
			delta_x = -0.0717;
			plyrite.setTexture(plyr_lu);
			isRotated = true;
			angle = std::atan2(delta_y, delta_x) * 180.0 / 3.14159;
		}
		else if (s == "ru")
		{ // right upwards
			delta_y = 0.0717;
			delta_x = 0.0717;
			plyrite.setTexture(plyr_ru);
			isRotated = true;
			angle = std::atan2(delta_y, delta_x) * 180.0 / 3.14159;
		}
		else if (s == "ls")
		{ // left downwards
			delta_y = -0.0717;
			delta_x = -0.0717;
			plyrite.setTexture(plyr_ls);
			isRotated = true;
			angle = std::atan2(delta_y, delta_x) * 180.0 / 3.14159;
		}
		else if (s == "rs")
		{ // right downwards
			delta_y = -0.0717;
			delta_x = 0.0717;
			plyrite.setTexture(plyr_rs);
			isRotated = true;
			angle = std::atan2(delta_y, delta_x) * 180.0 / 3.14159;
		}

		delta_x *= speed;
		delta_y *= speed;

		plyrite.move(sf::Vector2f(delta_x, delta_y));
		speed=0.1; //default speed
	}
};
