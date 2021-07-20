#include "Object.h"

Object::Object(float posX, float posY)
{
    sprite.setPosition(posX, posY);
    sprite.setScale(Vector2f(BLOCK_WIDTH / SPRITE_WIDTH, BLOCK_HEIGHT / SPRITE_HEIGHT));
}

Vector2f Object::getPos()
{
    return sprite.getPosition();
}

void Object::draw(RenderTarget& target, RenderStates state) const
{
    target.draw(sprite, state);
}

void Object::move(Vector2f velocity)
{
    sprite.move(velocity);
}

Vector2i transformToBlockPos(Vector2f pos)
{
    Vector2i blockPos;
    blockPos.x = round(pos.x / BLOCK_WIDTH);
    blockPos.y = round(pos.y / BLOCK_HEIGHT);
    return blockPos;
}
