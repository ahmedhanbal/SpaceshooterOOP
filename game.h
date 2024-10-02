
#include <time.h>
#include "player.h"
#include "enemy.h"
#include "invader.h"
#include "monster.h"
#include "dragon.h"
#include "bomb.h"
#include <string>

const char title[] = "OOP-Project, Spring-2023";
struct timeManage
{
        // Time will store since how much time since last type of specific enemy was spawned
        // Sp will store how much time must be elapsed to spawn enemy of that same type
        float invaderTime;
        float invaderSp;
        float monsterTime;
        float monsterSp;
        float dragonTime;
        float dragonSp;
};

class Game
{
private:
        int t_invaders; // total invaders
        int t_monsters; // total monsters
        int t_dragon;   // total dragons
        int bombsize;   // total bomb or enemy ammo fires
        bool isPaused;  // if game is Paused
        bool isOver;    // if game is over
public:
        Sprite background,scoreM; // Game background sprite
        Texture bg_texture,scrM;
        Text score,health;
        Font font;
        Player *p;        // player
        Enemy **invaders; // for storing invaders
        Enemy **monsters; // for storing monsters
        Enemy **dragon;   // for storing dragons
        Bomb **bombsArr;  // for strong enemy fire weapons
        timeManage inst;  // for storing enemy spawn
        Game()
        {
                p = new Player("img/player_ship.png");
                bg_texture.loadFromFile("img/bg_game.jpeg");
                background.setTexture(bg_texture);
                background.setScale(1, 1);
                scrM.loadFromFile("img/frame.png");
                scoreM.setTexture(scrM);
                scoreM.setPosition(780,0);
                font.loadFromFile("font/UbuntuNerdFont-Bold.ttf");
                score.setFont(font);
                health.setFont(font);
                score.setString("SCORE");
                health.setString("HEALTH");
                score.setCharacterSize(30);
                health.setCharacterSize(30);
                score.setPosition(850,200);
                health.setPosition(845,400);
                // Initializing to zero, nullptr and default values
                t_invaders = 0;
                t_monsters = 0;
                t_dragon = 0;
                bombsize = 0;
                invaders = nullptr;
                monsters = nullptr;
                dragon = nullptr;
                bombsArr = nullptr;
                inst = {0, 0.4, 0, 1.5, 0, 10}; // set spawn time
                isPaused = false;
                isOver = false;
        }

        bool isGamePaused() const
        {
                return isPaused;
        }
        bool getIsOver() const
        {
                return isOver;
        }
        void UpdateScore()
        {
                std::string s=std::to_string(p->health);
                p->helth.setString(s);
                s=std::to_string(p->kills);
                p->kill.setString(s);
        }
        void spawnEnemy()
        {
                if (inst.invaderTime >= inst.invaderSp) // Spawn invader every invaderSp seconds
                {
                        Enemy **temp = new Enemy *[t_invaders + 1]; // created an pointer array of 1 greater than previous size
                        for (int i = 0; i < t_invaders; i++)
                        {
                                temp[i] = invaders[i]; // copying previous into new arary
                        }
                        temp[t_invaders] = new Invader(); // adding new enemy at last index
                        delete[] invaders;                // deletin old
                        invaders = temp;                  // storing address of new array in old
                        inst.invaderTime = 0;             // setting to zero as an invader has spawned
                        t_invaders++;                     // total invaders increased
                }

                if (inst.monsterTime >= inst.monsterSp) // Spawn monster every monsterSp seconds
                {
                        Enemy **temp = new Enemy *[t_monsters + 1]; // created an pointer array of 1 greater than previous size
                        for (int i = 0; i < t_monsters; i++)
                        {
                                temp[i] = monsters[i]; // copying previous into new arary
                        }
                        temp[t_monsters] = new Monster(); // adding new enemy at last index
                        delete[] monsters;                // deleting old
                        monsters = temp;
                        inst.monsterTime = 0; // setting it to zero as a monster has spawned
                        t_monsters++;         // monsters increased
                }

                if (inst.dragonTime >= inst.dragonSp) // Spawn dragon every dragonSp seconds
                {
                        // Following same logic as invaders and monsters to spawn dragon
                        Enemy **temp = new Enemy *[t_dragon + 1];
                        for (int i = 0; i < t_dragon; i++)
                        {
                                temp[i] = dragon[i];
                        }
                        temp[t_dragon] = new Dragon();
                        delete[] dragon;
                        dragon = temp;
                        inst.dragonTime = 0;
                        t_dragon++;
                }
        }
        bool isCollision(Boundary &b1, Boundary &b2) // collision function that checks collision based on boundary values of two sprites
        {
                // comparing all GlobalBounds() values to return true or false if they are intersecting
                //  just like sfml's intersects function
                return b1.left < b2.left + b2.width && b1.left + b1.width > b2.left && b1.top < b2.top + b2.height && b1.top + b1.height > b2.top;
        }
        bool checkCollisionPE(Player *&player, Enemy *&enemy) // Enemy and Player Collision
        {
                // First getting boundary values of player and enemy
                Boundary pArea = player->getBoundary();
                Boundary eArea = enemy->getBoundary();
                // then calling collision function
                return isCollision(pArea, eArea);
        }
        bool checkCollisionBE(Enemy *&enemy, Bullet *&bullet) // Enemy and Player's bullet Collision
        {
                // First getting boundary values of enemy and player's bullet
                Boundary bArea = bullet->getBoundary();
                Boundary eArea = enemy->getBoundary();
                // then calling isCollision
                return isCollision(bArea, eArea);
        }
        bool checkCollisionPB(Player *&player, Bomb *&bomb) // Player and Enemy's bomb or laser or any weapon collision
        {
                // First getting boundary values of enemy's weapon and player
                Boundary pArea = player->getBoundary();
                Boundary bArea = bomb->getBoundary();
                // calling isCollision
                return isCollision(pArea, bArea);
        }
        void updateInvaders() // deals with deleting and calling collision fns of invader type enemies
        {
                for (int i = 0; i < t_invaders; i++)
                {
                        invaders[i]->move(p->plyrite);    // moving the invader downwards
                        if (invaders[i]->isOutOfBounds()) // if it is out of bottom max screen
                        {
                                // deleting and updating invaders array
                                delete invaders[i];
                                t_invaders--;
                                for (int j = i; j < t_invaders; j++)
                                {
                                        invaders[j] = invaders[j + 1];
                                }
                                i--;
                        }
                        else if (checkCollisionPE(p, invaders[i])) // calls collision bw player and invader
                        {
                                // decreasing health
                                invaders[i]->health--;
                                p->health--;
                                if (invaders[i]->health <= 0)
                                {
                                        // instead of deleting if health is zero, moving it out of screen
                                        invaders[i]->enemySprite.setPosition(0, 780 + invaders[i]->enemySprite.getGlobalBounds().height);
                                        p->kills++;
                                }
                        }
                }
                for (int i = 0; i < t_invaders; i++) // for invader and bullet collision
                {
                        for (int j = 0; j < p->bullsize; j++)
                        {
                                if (p->bulletsArr[j] == nullptr)
                                        continue;
                                else if (checkCollisionBE(invaders[i], p->bulletsArr[j]))
                                {
                                        p->bulletsArr[j]->bullet.move(1, -800); // moving it out of screen
                                                                                // decreasing health
                                        invaders[i]->health--;
                                        if (invaders[i]->health <= 0)
                                        {
                                                // instead of deleting if health is zero, moving it out of screen
                                                invaders[i]->enemySprite.setPosition(0, 780 + invaders[i]->enemySprite.getGlobalBounds().height);
                                                p->kills++;
                                        }
                                        break;
                                }
                        }
                }
        }
        void updateMonsters() // updating monsters
        {
                // same functionality is implemented as on invaders
                for (int i = 0; i < t_monsters; i++)
                {

                        monsters[i]->move(p->plyrite);
                        if (monsters[i]->isOutOfBounds())
                        {
                                delete monsters[i];
                                t_monsters--;
                                for (int j = i; j < t_monsters; j++)
                                {
                                        monsters[j] = monsters[j + 1];
                                }
                                i--;
                        }
                        else if (checkCollisionPE(p, monsters[i]))
                        {
                                monsters[i]->health--;
                                p->health--;
                                if (monsters[i]->health <= 0)
                                {
                                        monsters[i]->enemySprite.setPosition(0, 780 + monsters[i]->enemySprite.getGlobalBounds().height);
                                        p->kills++;
                                }
                        }
                }
                for (int i = 0; i < t_monsters; i++)
                {
                        for (int j = 0; j < p->bullsize; j++)
                        {
                                if (p->bulletsArr[j] == nullptr)
                                        continue;
                                if (checkCollisionBE(monsters[i], p->bulletsArr[j]))
                                {
                                        p->bulletsArr[j]->bullet.move(1, -800);
                                        monsters[i]->health--;
                                        if (monsters[i]->health <= 0)
                                        {
                                                monsters[i]->enemySprite.setPosition(0, 780 + monsters[i]->enemySprite.getGlobalBounds().height);
                                                p->kills++;
                                        }
                                        break;
                                }
                        }
                }
        }
        void updateDragon() // updating dragon
        {
                // same functionality is implemented as on invaders
                for (int i = 0; i < t_dragon; i++)
                {
                        dragon[i]->move(p->plyrite);
                        if (dragon[i]->isOutOfBounds())
                        {
                                delete dragon[i];
                                t_dragon--;
                                for (int j = i; j < t_dragon; j++)
                                {
                                        dragon[j] = dragon[j + 1];
                                }
                                i--;
                        }
                        else if (checkCollisionPE(p, dragon[i]))
                        {
                                dragon[i]->health--;
                                p->health--;
                                if (dragon[i]->health <= 0)
                                {
                                        dragon[i]->enemySprite.setPosition(0, 780 + dragon[i]->enemySprite.getGlobalBounds().height);
                                        p->kills++;
                                }
                        }
                }
                for (int i = 0; i < t_dragon; i++)
                {
                        for (int j = 0; j < p->bullsize; j++)
                        {
                                if (p->bulletsArr[j] == nullptr)
                                        continue;
                                if (checkCollisionBE(dragon[i], p->bulletsArr[j]))
                                {
                                        p->bulletsArr[j]->bullet.move(1, -800);
                                        dragon[i]->health--;
                                        if (dragon[i]->health <= 0)
                                        {
                                                dragon[i]->enemySprite.setPosition(0, 780 + dragon[i]->enemySprite.getGlobalBounds().height);
                                                p->kills++;
                                        }
                                        break;
                                }
                        }
                }
        }

        void updateEnemies() // calling all enemy update FNs
        {
                updateInvaders();
                updateMonsters();
                updateDragon();
        }
        void enemiesFire() // enemies fire fn
        {
                for (int i = 0; i < t_invaders; i++)
                {
                        // if invaders have ammo left and also
                        // their x location is almost same as x location of player
                        // this is done by taking absolute of enemy - player position which will give positive x distance bw enemy and player
                        // if that distance is less than player's width that means it is in enemy's vicinity
                        if (invaders[i]->ammo > 0 && abs(invaders[i]->enemySprite.getPosition().x - p->plyrite.getPosition().x) < p->plyrite.getGlobalBounds().width)
                        {
                                invaders[i]->fire(&bombsArr, bombsize);
                                break;
                        }
                }
                for (int i = 0; i < t_monsters; i++)
                {
                        // the same logic as of invader is applied
                        if (monsters[i]->ammo > 0 && abs(monsters[i]->enemySprite.getPosition().x - p->plyrite.getPosition().x) < p->plyrite.getGlobalBounds().width)
                        {
                                monsters[i]->fire(&bombsArr, bombsize);
                        }
                }
                for (int i = 0; i < t_dragon; i++)
                {
                        // same logic as of invader and monster
                        if (dragon[i]->ammo > 0 && abs(monsters[i]->ammo > 0 && dragon[i]->enemySprite.getPosition().x - p->plyrite.getPosition().x) < p->plyrite.getGlobalBounds().width)
                        {
                                dragon[i]->fire(&bombsArr, bombsize);
                        }
                }
        }
        void bombPlyrColl()
        {
                // player and enemy's collsion
                for (int i = 0; i < bombsize; i++)
                {
                        if (checkCollisionPB(p, bombsArr[i]))
                        {
                                bombsArr[i]->bomb.setPosition(780, 780 + bombsArr[i]->bomb.getGlobalBounds().height);
                                p->health--;
                        }
                }
        }
        void bombDelete() // updates and delets enemy's ammo
        {
                int counter = 0;
                for (int i = 0; i < bombsize; i++)
                {
                        if (!(bombsArr[i]->x_ax < 0 || bombsArr[i]->x_ax > 780 || bombsArr[i]->y_ax < 0 || bombsArr[i]->y_ax > 780))
                        { // If the bullet is still on screen keep it in array
                                bombsArr[counter] = bombsArr[i];
                                counter++;
                        }
                        else
                        { // If the bullet is off screen, delete it
                                delete bombsArr[i];
                        }
                }
                bombsize = counter;
        }
        void bombMove() // moves enemy's ammo
        {
                for (int i = 0; i < bombsize; i++)
                {
                        bombsArr[i]->movebomb();
                }
        }
        void bombDraw(RenderWindow &window) // draws enemy's ammo or weapon
        {
                for (int i = 0; i < bombsize; i++)
                {
                        window.draw(bombsArr[i]->bomb);
                }
        }
        void drawEnemy(RenderWindow &window) // draws all types of enemies
        {
                for (int i = 0; i < t_invaders; i++) // drawing invaders
                {
                        if (invaders[i]) // an extra precaution to avoid segmentation fault
                        {
                                window.draw(invaders[i]->enemySprite);
                        }
                }
                for (int i = 0; i < t_monsters; i++) // monsters
                {
                        if (monsters[i])
                        {
                                window.draw(monsters[i]->enemySprite);
                        }
                }
                for (int i = 0; i < t_dragon; i++) // and drawing dragon
                {
                        if (dragon[i])
                                window.draw(dragon[i]->enemySprite);
                }
        }

        void drawBullet(RenderWindow &window) // drawing player's bullets
        {
                for (int i = 0; i < p->bullsize; i++)
                {
                        if (!(p->bulletsArr[i]->bullet.getPosition().y < 0))
                                window.draw(p->bulletsArr[i]->bullet);
                }
        }

        bool isGameOver() // GameOver function, sets everything to zero , deletes dynamic arrays
        {
                if (p->health < 0)
                {
                        isOver = true;
                        isPaused = true;
                }
                return isOver;
        }
        void clearMemory()
        {
                for (int i = 0; i < p->bullsize; i++)
                {
                        delete p->bulletsArr[i];
                }
                for (int i = 0; i < bombsize; i++)
                {
                        delete bombsArr[i];
                }
                for (int i = 0; i < t_invaders; i++)
                {
                        delete invaders[i];
                }
                for (int i = 0; i < t_monsters; i++)
                {
                        delete monsters[i];
                }
                for (int i = 0; i < t_dragon; i++)
                {
                        delete dragon[i];
                }
                p->bullsize = 0;
                bombsize = 0;
                t_invaders = 0;
                t_monsters = 0;
                t_dragon = 0;
                inst = {0, 0, 0, 0, 0, 0};
                delete [] invaders;
                delete [] monsters;
                delete [] dragon;
                invaders=nullptr; monsters=nullptr; dragon=nullptr;
                delete [] p->bulletsArr;
                p->bulletsArr=nullptr;
                delete [] bombsArr;
                bombsArr=nullptr;
                delete p;
                p = nullptr;
        }
        void start_game(RenderWindow &window) // main game runner function
        {
                srand(time(0));
                Clock clock;
                while (window.isOpen())
                {
                        float time = clock.getElapsedTime().asSeconds() - time;
                        clock.restart();
                        inst.invaderTime += time;
                        inst.monsterTime += time;
                        inst.dragonTime += time;
                        Event e;
                        while (window.pollEvent(e))
                        {
                                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                                        window.close();      // close the game
                                if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)
                                {
                                        isPaused = true;
                                        return; // Return from the function to pause the game
                                }
                        }
                        // All the key combinations
                        if (Keyboard::isKeyPressed(Keyboard::Left))  // If left key is pressed
                                p->move("l");                        // Player will move to left
                        if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
                                p->move("r");                        // player will move to right
                        if (Keyboard::isKeyPressed(Keyboard::Up))    // If up key is pressed
                                p->move("u");                        // playet will move upwards
                        if (Keyboard::isKeyPressed(Keyboard::Down))  // If down key is pressed
                                p->move("d");                        // player will move downwards
                        if ((Keyboard::isKeyPressed(Keyboard::Up)) && (Keyboard::isKeyPressed(Keyboard::Right)))
                                p->move("ru");
                        if ((Keyboard::isKeyPressed(Keyboard::Up)) && (Keyboard::isKeyPressed(Keyboard::Left)))
                                p->move("lu");
                        if ((Keyboard::isKeyPressed(Keyboard::Down)) && (Keyboard::isKeyPressed(Keyboard::Right)))
                                p->move("rs");
                        if ((Keyboard::isKeyPressed(Keyboard::Down)) && (Keyboard::isKeyPressed(Keyboard::Left)))
                                p->move("ls");
                        if (Mouse::isButtonPressed(Mouse::Left))
                                p->fire();
                        if (Keyboard::isKeyPressed(Keyboard::LShift)) // speed up or booster
                                p->speed = 0.3;

                        ////////////////////////////////////////////////
                        /////  Call your functions here            ////
                        p->bulletmove();
                        p->moveAround();
                        p->deleteBullet();
                        spawnEnemy();
                        updateEnemies();
                        enemiesFire();
                        bombMove();
                        bombDelete();
                        bombPlyrColl();
                        UpdateScore();
                        if (isGameOver())
                        {
                                isOver=true;
                                isPaused=false;
                                clearMemory();
                                return;
                        }
                        //////////////////////////////////////////////

                        window.clear(Color::Black); // clears the screen
                        window.draw(background);    // setting background
                        drawBullet(window);         // drawing bullets
                        bombDraw(window);           // bombs or enemy's ammo
                        drawEnemy(window);          // drawing enemy
                        window.draw(p->plyrite);    // setting player on screen
                        window.draw(scoreM);
                        window.draw(score);
                        window.draw(p->kill);
                        window.draw(health);
                        window.draw(p->helth);
                        window.display();           // Displying all the sprites
                        p->plyrite.setTexture(p->plyrTex); // setting player's texture to default to cope with rotation
                }
        }
};
