#pragma once
#include "Object.h"
#include <vector>
#include "Fire.h"
#include "Box.h"

using namespace sf;
using namespace std;

class Bomb : public Object
{
public:
    Bomb(float posX, float posY, int cid, int str);
    static vector<Bomb*> bombs;
    bool shouldExpole(Time dt);
    vector<int> explode(vector<Fire*> &fires, int (&board)[BOARD_HEIGHT][BOARD_WIDTH], vector<Box*> &boxes);
    int getStrength();
    int getId();
    int getCreatorId();
    
    
private:
    Time timeToExplosion;
    int strength;
    int id;
    int creatorId;
    void loadTexture(int x, int y);
};