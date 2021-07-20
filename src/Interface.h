#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include <string>

using namespace std;
using namespace sf;

class Interface
{
public:
    Interface();
    void draw(RenderWindow &window, vector<Player*> &players);

private:
    RectangleShape *background;
    void drawFaces(RenderWindow &window);
    void drawLifes(RenderWindow &window, vector<Player*> &players);
    Font font;
};