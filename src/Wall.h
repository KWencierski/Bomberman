#pragma once
#include "Object.h"

using namespace sf;

class Wall : public Object
{
public:
    Wall(float posX, float posY);
    
private:
    void loadTexture(int x, int y);
};