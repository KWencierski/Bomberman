#pragma once
#include "Object.h"
#include "PowerUp.h"
#include <time.h>
#include <stdlib.h>

using namespace sf;
using namespace std;

class Box : public Object
{
public:
    Box(float posX, float posY);
    static vector<PowerUp*> powerUps;
    ~Box();

private:
    void loadTexture(int x, int y);
};
