#include "Wall.h"

Wall::Wall(float posX, float posY) : Object(posX, posY)
{
    loadTexture(0, 0);
}

void Wall::loadTexture(int x, int y)
{
    texture.loadFromFile("images/wall.png", IntRect(x, y, 16, 16));
    sprite.setTexture(texture); 
}