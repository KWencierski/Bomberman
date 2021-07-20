#pragma once
#include "Object.h"
#include <vector>

using namespace sf;
using namespace std;

class Fire : public Object
{
public:
    Fire(float posX, float posY, int x, int y);
    bool shouldDisappear(Time dt);
private:
    Time timeToDisappear;
    void loadTexture(int x, int y);
};