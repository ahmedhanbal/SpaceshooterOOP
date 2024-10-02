
#include "game.h"
class Menu
{
public:
    // add menu attributes here
    bool isNewGameSelected;
    Menu()
    {
        isNewGameSelected = true;
    }
    void display_menu()
    {

        Game g;
        RenderWindow menu(VideoMode(1000, 780), "SPACESHOOTER - MENU");
        Sprite background;
        Texture bg_tex;
        bg_tex.loadFromFile("img/bg_menu.jpeg");
        background.setTexture(bg_tex);
        // Loading and setting text and fonts
        Text newG, exitG, contG, gOver;
        Font font;
        font.loadFromFile("font/UbuntuNerdFont-Bold.ttf");
        newG.setFont(font);
        exitG.setFont(font);
        contG.setFont(font);
        gOver.setFont(font);
        
        newG.setString("NEW GAME");
        contG.setString("CONTINUE");
        exitG.setString("EXIT");
        gOver.setString("GAME OVER");

        newG.setCharacterSize(50);
        contG.setCharacterSize(50);
        exitG.setCharacterSize(50);
        gOver.setCharacterSize(80);

        newG.setPosition(350, 200);
        contG.setPosition(350, 200);
        exitG.setPosition(430, 400);
        gOver.setPosition(250,200);

         
        newG.setFillColor(Color::Blue);
        gOver.setFillColor(Color::Red);
        contG.setFillColor(Color::White);

        while (menu.isOpen()) // main menu loop
        {
            Event e;
            while (menu.pollEvent(e)) // event to make interactive menu
            {
                if (e.type == Event::Closed) 
                    menu.close();            
                else if (e.type == Event::KeyPressed)
                {
                    if (e.key.code == Keyboard::Up) 
                    {
                        isNewGameSelected = true;
                        if(!g.isGamePaused()) newG.setFillColor(Color::Blue);
                        else contG.setFillColor(Color::Blue);
                        exitG.setFillColor(Color::White);
                    }
                    else if (e.key.code == Keyboard::Down) 
                    {
                        isNewGameSelected = false;
                        exitG.setFillColor(Color::Blue);
                        if(!g.isGamePaused()) newG.setFillColor(Color::White);
                        else contG.setFillColor(Color::White);
                    }
                    else if (e.key.code == Keyboard::Enter) 
                    {
                        if (isNewGameSelected)
                            g.start_game(menu); // Start the game
                        else
                            menu.close(); // Exit the menu
                    }
                }
            }
            //diaplaying menu items
            menu.clear(Color::Black);
            menu.draw(background);
            if(g.isGamePaused()) menu.draw(contG);
            else if(g.getIsOver()) menu.draw(gOver);
            else menu.draw(newG);
            menu.draw(exitG);
            menu.display();
        }
    }
};
