#pragma once
#include "Player.h"
#include "Wall.h"
#include "Bomb.h"
#include <vector>
#include "Fire.h"
#include "Box.h"
#include <stdlib.h>
#include <time.h>
#include "Interface.h"
#include "PowerUp.h"

using namespace std;
using namespace sf;

#define NUMBER_OF_PLAYERS 2

class Game
{
public:
    void createWalls();
    void createPlayers();
    void updatePlayers();
    void drawPlayers();
    void drawWalls();
    void drawBombs();
    Game(RenderWindow &window);
    void getBombs();
    void decreaseTimers(Time dt);
    void drawFires();
    void checkDamage();
    void spawnBoxes(float spawnChance);
    void drawBoxes();
    void drawBackground();
    void drawInterface();
    void drawPowerUps();
    void getNewPowerUps();
    void checkPowerUpPickUp();
    bool getGameState();
    void showGameOverScreen();

private: 
    RenderWindow *window;
    int board[BOARD_HEIGHT][BOARD_WIDTH] = {};
    vector<Object*> walls;
    vector<Player*> players;
    vector<Bomb*> bombs;
    vector<Fire*> fires;
    int getBombPos(int id);
    vector<Box*> boxes;
    Interface *interface;
    vector<PowerUp*> powerUps;
    bool isGameOver;
    int loser;
};