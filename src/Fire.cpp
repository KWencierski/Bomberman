#include "Fire.h"

Fire::Fire(float posX, float posY, int x, int y) : Object(posX, posY)
{
    loadTexture(x, y);
    timeToDisappear = seconds(2.0);
}

bool Fire::shouldDisappear(Time dt)
{
    timeToDisappear -= dt;
    if (timeToDisappear < seconds(0))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

void Fire::loadTexture(int x, int y)
{
    texture.loadFromFile("images/fire.png", IntRect(x, y, 16, 16));
    sprite.setTexture(texture); 
}