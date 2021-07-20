#pragma once
#include "Object.h"
#include "Player.h"

using namespace sf;

class PowerUp : public Object
{
public:
    PowerUp(float posX, float posY, int i);
    void givePower(Player *player);

private:
    int type;
    void loadTexture(int x, int y);
};