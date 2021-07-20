#include "Box.h"

Box::Box(float posX, float posY) : Object(posX, posY)
{
    loadTexture(0, 0);
}

void Box::loadTexture(int x, int y)
{
    texture.loadFromFile("images/box.png", IntRect(x, y, 16, 16));
    sprite.setTexture(texture); 
}

vector<PowerUp*> Box::powerUps;

Box::~Box()
{
    if (rand() % 3 == 0)
    {
        powerUps.push_back(new PowerUp(getPos().x, getPos().y, rand() % 4));
    }
}