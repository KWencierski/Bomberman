#include "PowerUp.h"

PowerUp::PowerUp(float posX, float posY, int i) : Object(posX, posY), type(i)
{
    loadTexture(16 * type, 0);
}

void PowerUp::loadTexture(int x, int y)
{
    texture.loadFromFile("images/powerUps.png", IntRect(x, y, 16, 16));
    sprite.setTexture(texture); 
}

void PowerUp::givePower(Player *player)
{
    switch(type)
    {
    case 0:
        player->addOneBombStrength();
        break;

    case 1:
        player->restoreBomb();
        break;

    case 2:
        player->addOneSpeed();
        break;

    case 3:
        player->addOneLife();
        break;
    }
}