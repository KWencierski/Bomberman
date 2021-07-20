#include "Bomb.h"

Bomb::Bomb(float posX, float posY, int cid, int str) : Object(posX, posY), strength(str) ,creatorId(cid)
{
    loadTexture(0, 0);
    timeToExplosion = seconds(3.0);
    id = static_cast<int>(posY / BLOCK_HEIGHT) * BOARD_WIDTH + static_cast<int>(posX / BLOCK_WIDTH);
}

vector<Bomb*> Bomb::bombs;

bool Bomb::shouldExpole(Time dt)
{
    timeToExplosion -= dt;
    if (timeToExplosion <= seconds(0))
    {
        return true;
    }
    else if (timeToExplosion <= seconds(1))
    {
        loadTexture(32, 0);
        return false;
    }
    else if (timeToExplosion <= seconds(2))
    {
        loadTexture(16, 0);
        return false;
    }
    else
    {
        return false;
    }
}

vector<int> Bomb::explode(vector<Fire*> &fires, int (&board)[BOARD_HEIGHT][BOARD_WIDTH], vector<Box*> &boxes)
{
    Vector2f pos = getPos();
    Vector2i boardPos = transformToBlockPos(pos);
    fires.push_back(new Fire(pos.x, pos.y, 16, 0));
    vector<int> additionalExplosions;
    // 0 - none, 1 - wall, 2 - box, 3 - bomb
    // Left
    for (int i = 1; i <= strength; i++)
    {
        if (board[boardPos.y][boardPos.x - i] == 0)
        {
            fires.push_back(new Fire(pos.x - BLOCK_WIDTH * i, pos.y, 0, 0));
        }
        else if (board[boardPos.y][boardPos.x - i] == 2)
        {
            for (int j = 0; j < static_cast<int>(boxes.size()); j++)
            {
                if (boxes[j]->getPos() == Vector2f((boardPos.x - i) * BLOCK_WIDTH, boardPos.y * BLOCK_HEIGHT))
                {
                    board[boardPos.y][boardPos.x - i] = 0;
                    fires.push_back(new Fire(pos.x - BLOCK_WIDTH * i, pos.y, 0, 0));
                    delete boxes[j];
                    boxes.erase(boxes.begin() + j);
                }
            }
            break;
        }
        else if (board[boardPos.y][boardPos.x - i] == 3)
        {
            additionalExplosions.push_back((boardPos.x - i) + boardPos.y * BOARD_WIDTH);
            break;
        }
        else 
        {
            break;
        }
    }
    // Right
    for (int i = 1; i <= strength; i++)
    {
        if (board[boardPos.y][boardPos.x + i] == 0)
        {
            fires.push_back(new Fire(pos.x + BLOCK_WIDTH * i, pos.y, 0, 0));
        }
        else if (board[boardPos.y][boardPos.x + i] == 2)
        {
            for (int j = 0; j < static_cast<int>(boxes.size()); j++)
            {
                if (boxes[j]->getPos() == Vector2f((boardPos.x + i) * BLOCK_WIDTH, boardPos.y * BLOCK_HEIGHT))
                {
                    board[boardPos.y][boardPos.x + i] = 0;
                    fires.push_back(new Fire(pos.x + BLOCK_WIDTH * i, pos.y, 0, 0));
                    delete boxes[j];
                    boxes.erase(boxes.begin() + j);
                }
            }
            break;
        }
        else if (board[boardPos.y][boardPos.x + i] == 3)
        {
            additionalExplosions.push_back((boardPos.x + i) + boardPos.y * BOARD_WIDTH);
            break;
        }
        else
        {
            break;
        }
    }
    // Up
    for (int i = 1; i <= strength; i++)
    {
        if (board[boardPos.y - i][boardPos.x] == 0)
        {
            fires.push_back(new Fire(pos.x, pos.y - BLOCK_HEIGHT * i, 32, 0));
        }
        else if (board[boardPos.y - i][boardPos.x] == 2)
        {
            for (int j = 0; j < static_cast<int>(boxes.size()); j++)
            {
                if (boxes[j]->getPos() == Vector2f(boardPos.x * BLOCK_WIDTH, (boardPos.y - i) * BLOCK_HEIGHT))
                {
                    board[boardPos.y - i][boardPos.x] = 0;
                    fires.push_back(new Fire(pos.x, pos.y - BLOCK_HEIGHT * i, 32, 0));
                    delete boxes[j];
                    boxes.erase(boxes.begin() + j);
                }
            }
            break;
        }
        else if (board[boardPos.y - i][boardPos.x] == 3)
        {
            additionalExplosions.push_back(boardPos.x + (boardPos.y - i) * BOARD_WIDTH);
            break;
        }
        else
        {
            break;
        }
    }
    // Down
    for (int i = 1; i <= strength; i++)
    {
        if (board[boardPos.y + i][boardPos.x] == 0)
        {
            fires.push_back(new Fire(pos.x, pos.y + BLOCK_HEIGHT * i, 32, 0));
        }
        else if (board[boardPos.y + i][boardPos.x] == 2)
        {
            for (int j = 0; j < static_cast<int>(boxes.size()); j++)
            {
                if (boxes[j]->getPos() == Vector2f(boardPos.x * BLOCK_WIDTH, (boardPos.y + i) * BLOCK_HEIGHT))
                {
                    board[boardPos.y + i][boardPos.x] = 0;
                    fires.push_back(new Fire(pos.x, pos.y + BLOCK_HEIGHT * i, 32, 0));
                    delete boxes[j];
                    boxes.erase(boxes.begin() + j);
                }
            }
            break;
        }
        else if (board[boardPos.y + i][boardPos.x] == 3)
        {
            additionalExplosions.push_back(boardPos.x + (boardPos.y + i) * BOARD_WIDTH);
            break;
        }
        else
        {
            break;
        }
    }
    return additionalExplosions;
}

int Bomb::getStrength()
{
    return strength;
}

int Bomb::getId()
{
    return id;
}

int Bomb::getCreatorId()
{
    return creatorId;
}

void Bomb::loadTexture(int x, int y)
{
    texture.loadFromFile("images/bomb.png", IntRect(x, y, 16, 16));
    sprite.setTexture(texture); 
}