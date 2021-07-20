#include "Game.h"
#include <vector>
#include <Windows.h>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bomberman");
    window.setFramerateLimit(60);
    Game game(window);
    
    game.createPlayers();
    
    game.createWalls();
    game.spawnBoxes(0.75);
    
    Event event;
    Clock clock;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        game.decreaseTimers(clock.restart());
        game.updatePlayers();
        game.checkDamage();

        window.clear();

        game.drawBackground();
        game.drawWalls();

        game.getNewPowerUps();
        game.checkPowerUpPickUp();
        game.drawPowerUps();

        game.drawBoxes();
        game.getBombs();
        game.drawBombs();
        game.drawPlayers();
        game.drawFires();
        game.drawInterface();

        if(game.getGameState())
        {
            game.showGameOverScreen();
        }

        window.display();
    }

    return 0;
}

