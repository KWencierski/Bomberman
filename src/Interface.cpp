#include "Interface.h"

Interface::Interface()
{
    background = new RectangleShape(Vector2f(WINDOW_WIDTH - BLOCK_WIDTH * BOARD_WIDTH, WINDOW_HEIGHT));
    background->setPosition(BLOCK_WIDTH * BOARD_WIDTH, 0);
    background->setFillColor(Color(50, 50, 50));

    font.loadFromFile("font/arial.ttf");
}

void Interface::draw(RenderWindow &window, vector<Player*> &players)
{
    window.draw(*background);
    drawFaces(window);
    drawLifes(window, players);
}

void Interface::drawFaces(RenderWindow &window)
{
    Texture texture[2];
    Sprite sprite[2]; 

    sprite[0].setPosition(BOARD_WIDTH * BLOCK_WIDTH + BLOCK_WIDTH / 4, BLOCK_HEIGHT / 4);
    sprite[0].setScale(19.0f, 19.0f);
    texture[0].loadFromFile("images/faces.png", IntRect(3, 5, 11, 7));
    sprite[0].setTexture(texture[0]); 

    sprite[1].setPosition(BOARD_WIDTH * BLOCK_WIDTH +  7 * BLOCK_WIDTH / 8, WINDOW_HEIGHT / 2);
    sprite[1].setScale(19.0f, 19.0f);
    texture[1].loadFromFile("images/faces.png", IntRect(21, 4, 7, 8));
    sprite[1].setTexture(texture[1]); 

    window.draw(sprite[0]);
    window.draw(sprite[1]);
}

void Interface::drawLifes(RenderWindow &window, vector<Player*> &players)
{
    Sprite heartSprite;
    Texture heartTexture;
    heartSprite.setPosition(BOARD_WIDTH * BLOCK_WIDTH + 3 * BLOCK_WIDTH / 4, 160);
    heartSprite.setScale(0.25f, 0.25f);
    heartTexture.loadFromFile("images/heart.png", IntRect(0, 0, 254, 254));
    heartSprite.setTexture(heartTexture); 
    window.draw(heartSprite);

    heartSprite.setPosition(BOARD_WIDTH * BLOCK_WIDTH + 3 * BLOCK_WIDTH / 4, 160 + WINDOW_HEIGHT / 2);
    window.draw(heartSprite);

    Text text;
    text.setFont(font);
    text.setFillColor(Color(255, 255, 255));
    text.setCharacterSize(70);
    for (int i = 0; i < 2; i++)
    {
        if (i == 1)
        {
            text.setPosition(BLOCK_WIDTH * BOARD_WIDTH + 2.2 * BLOCK_WIDTH , WINDOW_HEIGHT / 5);
            text.setString("x" + to_string(players[i]->getLifes()));
            window.draw(text);
        }
        else 
        {
            text.setPosition(BLOCK_WIDTH * BOARD_WIDTH + 2.2 * BLOCK_WIDTH , WINDOW_HEIGHT / 5 + WINDOW_HEIGHT / 2);
            text.setString("x" + to_string(players[i]->getLifes()));
            window.draw(text);
        }
    }
}
