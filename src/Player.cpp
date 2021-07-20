#include "Player.h"
#include "Bomb.h"

Player::Player(float posX, float posY, int c) : Object(posX, posY), controls(c)
{
    if (c == 0)
    {
        textureV = Vector2i(0, 0);
    }
    else
    {
        textureV = Vector2i(0, 17);
    }

    loadTexture(textureV.x, textureV.y);
    lifes = 3;
    bombsAvailable = 1;
    playerVelocity = 2.0f;
    bombStrength = 2;
    isGameOver = false;
}

void Player::update()
{
    Vector2f pos = getPos();
    Vector2i boardPos = transformToBlockPos(pos);
    if (!isGameOver)
    {
    if (Keyboard::isKeyPressed(keys[controls][0]) && this->canMove(0))
    {
        loadTexture(16 * 3, textureV.y);
        if(abs(pos.y - (boardPos.y * BLOCK_HEIGHT)) < playerVelocity)
        {
            velocity.x = -playerVelocity;
        }
        else if (board[boardPos.y + 1][boardPos.x - 1] != 0 && 
            pos.y > boardPos.y * BLOCK_HEIGHT - playerVelocity)
        {
            velocity.y = -playerVelocity;
        }
        else if (board[boardPos.y - 1][boardPos.x - 1] != 0 && 
            pos.y < (boardPos.y + 1) * BLOCK_WIDTH + playerVelocity)
        {
            velocity.y = playerVelocity;
        }
        else
        {
            velocity.x = -playerVelocity;
        }
    }
    else if (Keyboard::isKeyPressed(keys[controls][1]) && this->canMove(1))
    {
        loadTexture(16 * 2, textureV.y);
        if(abs(pos.y - (boardPos.y * BLOCK_HEIGHT)) < playerVelocity)
        {
            velocity.x = playerVelocity;
        }
        else if (board[boardPos.y + 1][boardPos.x + 1] != 0 && 
            pos.y > boardPos.y * BLOCK_HEIGHT - playerVelocity)
        {
            velocity.y = -playerVelocity;
        }
        else if (board[boardPos.y - 1][boardPos.x + 1] != 0 && 
            pos.y < (boardPos.y + 1) * BLOCK_WIDTH + playerVelocity)
        {
            velocity.y = playerVelocity;
        }
        else
        {
            velocity.x = playerVelocity;
        }
    }
    else if (Keyboard::isKeyPressed(keys[controls][2]) && this->canMove(2))
    {
        loadTexture(0, textureV.y);
        if(abs(pos.x - (boardPos.x * BLOCK_WIDTH)) < playerVelocity)
        {
            velocity.y = -playerVelocity;
        }
        else if (board[boardPos.y - 1][boardPos.x + 1] != 0 && 
            pos.x > boardPos.x * BLOCK_WIDTH - playerVelocity)
        {
            velocity.x = -playerVelocity;
        }
        else if (board[boardPos.y - 1][boardPos.x - 1] != 0 && 
            pos.x < (boardPos.x + 1) * BLOCK_WIDTH + playerVelocity)
        {
            velocity.x = playerVelocity;
        }
        else
        {
            velocity.y = -playerVelocity;
        }
    }
    else if (Keyboard::isKeyPressed(keys[controls][3]) && this->canMove(3))
    {
        loadTexture(16, textureV.y);
        if(abs(pos.x - (boardPos.x * BLOCK_WIDTH)) < playerVelocity)
        {
            velocity.y = playerVelocity;
        }
        else if (board[boardPos.y - 1][boardPos.x + 1] != 0 && 
            pos.x > boardPos.x * BLOCK_WIDTH - playerVelocity)
        {
            velocity.x = -playerVelocity;
        }
        else if (board[boardPos.y - 1][boardPos.x - 1] != 0 && 
            pos.x < (boardPos.x + 1) * BLOCK_WIDTH + playerVelocity)
        {
            velocity.x = playerVelocity;
        }
        else
        {
            velocity.y = playerVelocity;
        }
    }
    else
    {
        velocity.x = 0;
        velocity.y = 0;
    }

    if(Keyboard::isKeyPressed(keys[controls][4]) && board[boardPos.y][boardPos.x] == 0 && bombsAvailable > 0)
    {
        bombsAvailable--;
        plantBomb(getCurrentBlock());
    }
    
    move(velocity);
    velocity.x = 0;
    velocity.y = 0;
    updateCurrentBlock();
    }
}

void Player::updateCurrentBlock()
{
    currentBlock = transformToBlockPos(getPos());
}

Vector2i Player::getCurrentBlock()
{
    return currentBlock;
}

void Player::getBoard(int a[][BOARD_WIDTH])
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            board[i][j] = a[i][j];
        }
    }
}

Vector2i Player::getCurrentExactBlock()
{
    Vector2i blockPos;
    blockPos.x = floor(getPos().x / BLOCK_WIDTH);
    blockPos.y = floor(getPos().y / BLOCK_HEIGHT);
    return blockPos;
}

bool Player::canMove(int dir)
{
    Vector2f pos = getPos();
    Vector2i boardPos = transformToBlockPos(pos);
    if (dir == 0)
    {
        if (pos.x > boardPos.x * BLOCK_WIDTH)
        {
            return true;
        }
        else if (board[boardPos.y][boardPos.x - 1] == 0)
        {
            return true;
        }
    }
    else if (dir == 1)
    {
        if (pos.x < boardPos.x * BLOCK_WIDTH)
        {
            return true;
        }
        else if (board[boardPos.y][boardPos.x + 1] == 0)
        {
            return true;
        }
    }
    else if (dir == 2)
    {
        if (pos.y > boardPos.y * BLOCK_HEIGHT)
        {
            return true;
        }
        else if (board[boardPos.y - 1][boardPos.x] == 0)
        {
            return true;
        }
    }
    else if (dir == 3)
    {
        if (pos.y < boardPos.y * BLOCK_HEIGHT)
        {
            return true;
        }
        else if (board[boardPos.y + 1][boardPos.x] == 0)
        {
            return true;
        }
    }
    return false;
}

void Player::plantBomb(Vector2i pos)
{
    Bomb *bomb = new Bomb(pos.x * BLOCK_WIDTH, pos.y * BLOCK_HEIGHT, controls, bombStrength);
    Bomb::bombs.push_back(bomb);
}

int Player::getLifes()
{
    return lifes;
}

void Player::hurt()
{
    immortalityTimeLeft = seconds(3);
    inImmortalityState = true;
    Color c = Color(255, 255, 255, 155);
    sprite.setColor(c);
    --lifes;
}

bool Player::getState()
{
    return inImmortalityState;
}

void Player::decreaseImmortalityTimeLeft(Time dt)
{
    immortalityTimeLeft -= dt;
    if (immortalityTimeLeft <= seconds(0))
    {
        Color c = Color(255, 255, 255, 255);
        sprite.setColor(c);
        inImmortalityState = false;
    }
}

void Player::restoreBomb()
{
    ++bombsAvailable;
}

void Player::addOneLife()
{
    ++lifes;
}

void Player::addOneSpeed()
{
    ++playerVelocity;
}

void Player::addOneBombStrength()
{
    ++bombStrength;
}

void Player::loadTexture(int x, int y)
{
    texture.loadFromFile("images/players.png", IntRect(x, y, 16, 16));
    sprite.setTexture(texture); 
}

void Player::gameOver()
{
    isGameOver = true;
}

int Player::getControls()
{
    return controls;
}