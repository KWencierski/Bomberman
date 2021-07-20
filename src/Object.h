#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;

#define SPRITE_WIDTH 16
#define SPRITE_HEIGHT 16
#define BLOCK_WIDTH 55.0
#define BLOCK_HEIGHT 55.0
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720 
#define BOARD_WIDTH 19
#define BOARD_HEIGHT 13

class Object : public sf::Drawable
{
public:
    Object(float posX, float posY);
    Vector2f getPos();
    void draw(RenderTarget& target, RenderStates state) const override;
    void move(Vector2f velocity);
    Texture texture;
    Sprite sprite;
    

private:
    virtual void loadTexture(int x, int y) = 0;
};

Vector2i transformToBlockPos(Vector2f pos);