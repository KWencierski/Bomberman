#pragma once
#include "Object.h"
#include <vector>
#include <math.h>

using namespace sf;
using namespace std;

class Player : public Object
{
public:
    Player(float posX, float posY, int con);
    void update();
    Vector2i getCurrentBlock();
    Vector2i getCurrentExactBlock();
    void getBoard(int a[][BOARD_WIDTH]);
    int getLifes();
    void hurt();
    bool getState();
    void decreaseImmortalityTimeLeft(Time dt);
    void restoreBomb();
    void addOneLife();
    void addOneSpeed();
    void addOneBombStrength();
    void gameOver();
    int getControls();

private:
    float playerVelocity;
    Vector2f velocity;
    int controls;
    Vector2i currentBlock;
    void updateCurrentBlock();
    const Keyboard::Key keys[2][5] = {Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up,
        Keyboard::Key::Down, Keyboard::Key::Enter, Keyboard::Key::A, Keyboard::Key::D, Keyboard::Key::W, 
        Keyboard::Key::S, Keyboard::Key::E};
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    void plantBomb(Vector2i pos);
    bool canMove(int dir);
    int lifes;
    bool inImmortalityState;
    Time immortalityTimeLeft;
    Vector2i textureV;
    int bombsAvailable;
    int bombStrength;
    bool isGameOver;
    void loadTexture(int x, int y);
};