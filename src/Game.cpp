#include "Game.h"

void Game::createWalls()
{
    for(int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if ((i == 0 || i == BOARD_HEIGHT - 1 || j == 0 || j == BOARD_WIDTH - 1) || (i % 2 == 0 && j % 2 == 0))
            {
                walls.push_back(new Wall(BLOCK_WIDTH * j, BLOCK_HEIGHT * i));
                board[i][j] = 1;
            }
        }
    }
}

void Game::createPlayers()
{
    players.push_back(new Player(55, 55, 0));
    players.push_back(new Player((BOARD_WIDTH - 2) * BLOCK_WIDTH, (BOARD_HEIGHT - 2) * BLOCK_HEIGHT, 1));
}

void Game::updatePlayers()
{
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        players[i]->getBoard(board);
        players[i]->update();
    }
}

void Game::drawPlayers()
{
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        window->draw(*players[i]);
    }
}

void Game::drawWalls()
{
    for (int i = 0; i < static_cast<int>(walls.size()); i++)
    {
        window->draw(*walls[i]);
    }
}

Game::Game(RenderWindow &w)
{
    srand(time(NULL));
    window = &w;
    Image icon;
    icon.loadFromFile("images/player.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    interface = new Interface();

    isGameOver = false;

}

void Game::getBombs()
{
    for (int i = 0; i < static_cast<int>((Bomb::bombs).size()); i++)
    {
        bombs.push_back(Bomb::bombs[i]);
        Vector2i blockPos = transformToBlockPos(Bomb::bombs[i]->getPos());
        board[blockPos.y][blockPos.x] = 3;
    }
    Bomb::bombs.clear();
}

void Game::drawBombs()
{
    for (int i = 0; i < static_cast<int>(bombs.size()); i++)
    {
        window->draw(*bombs[i]);
    }
}

void Game::decreaseTimers(Time dt)
{
    // Bombs
    vector<int> bombsToRemove;
    vector<int> additionalExposions;
    for (int i = 0; i < static_cast<int>(bombs.size()); i++)
    {
        if (bombs[i]->shouldExpole(dt))
        {
            vector<int> additionalExposions = bombs[i]->explode(fires, board, boxes);
            bombsToRemove.push_back(bombs[i]->getId());

            while (additionalExposions.size() > 0)
            {
                bool firstAlreadyInQueue = false;
                for (int i = 0; i < static_cast<int>(bombsToRemove.size()); i++)
                {
                    if (additionalExposions[0] == bombsToRemove[i])
                    {
                        firstAlreadyInQueue = true;
                        break;
                    } 
                }

                if (!firstAlreadyInQueue)
                {
                    vector<int> temp = bombs[getBombPos(additionalExposions[0])]->explode(fires, board, boxes);
                    vector<int> sum;
                    sum.reserve(additionalExposions.size() + temp.size());
                    sum.insert(sum.end(), additionalExposions.begin(), additionalExposions.end());
                    sum.insert(sum.end(), temp.begin(), temp.end());
                    additionalExposions = sum;
                    bombsToRemove.push_back(additionalExposions[0]);
                }

                additionalExposions.erase(additionalExposions.begin());
            }
            
        }
    }

    while (bombsToRemove.size() > 0)  
    {
        int current = bombsToRemove[bombsToRemove.size() - 1];
        bombsToRemove.pop_back();

        for (int i = 0; i < static_cast<int>(bombs.size()); i++)
        {
            if (bombs[i]->getId() == current)
            {
                Vector2i blockPos = transformToBlockPos(bombs[i]->getPos());
                board[blockPos.y][blockPos.x] = 0;
                players[bombs[i]->getCreatorId()]->restoreBomb();
                delete bombs[i];
                bombs.erase(bombs.begin() + i);
                continue;
            }
        }
    }
    
    // Fire disappering
    int numberOfFiresToRemove = 0;
    for (int i = 0; i < static_cast<int>(fires.size()); i++)
    {
        if ((*fires[i]).shouldDisappear(dt))
        {
            numberOfFiresToRemove++;
        }
    }

    if (numberOfFiresToRemove > 0)
    {
        for (int i = 0; i < numberOfFiresToRemove; i++)
        {
            delete fires[i];
        }
        fires.erase(fires.begin(), fires.begin() + numberOfFiresToRemove);
    }

    // Players immortality timer
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        if (players[i]->getState())
        {
            players[i]->decreaseImmortalityTimeLeft(dt);
        }
    }
}

void Game::drawFires()
{
    for (int i = 0; i < static_cast<int>(fires.size()); i++)
    {
        window->draw(*fires[i]);
    }
}

int Game::getBombPos(int id)
{
    for (int i = 0; i < static_cast<int>(bombs.size()); i++)
    {
        if (bombs[i]->getId() == id)
        {
            return i;
        }
    }
    return -1;
}

void Game::checkDamage()
{
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        Vector2i playerPos = players[i]->getCurrentBlock();
        for (int j = 0; j < static_cast<int>(fires.size()); j++)
        {
            Vector2i firePos = transformToBlockPos(fires[j]->getPos());
            if (playerPos == firePos && players[i]->getState() == false)
            {
                players[i]->hurt();
                if (players[i]->getLifes() <= 0)
                {
                    isGameOver = true;
                    for (int k = 0; k < static_cast<int>(players.size()); k++)
                    {
                        players[k]->gameOver();
                    }
                    loser = i;
                }
            }
        }
    }
}

void Game::spawnBoxes(float spawnChance)
{
    for (int i = 1; i < BOARD_HEIGHT - 1; i++)
    {
        for (int j = 1; j < BOARD_WIDTH - 1; j++)
        {
            if (!(board[i][j] != 0 || (i == 1 && j == 1) || (i == 1 && j == 2) || (i == 2 && j == 1) || 
                (i == BOARD_HEIGHT - 2 && j == BOARD_WIDTH - 2) || (i == BOARD_HEIGHT - 3 && j == BOARD_WIDTH - 2) ||
                (i == BOARD_HEIGHT - 2 && j == BOARD_WIDTH - 3)))
            {
                if (rand() % 100 < spawnChance * 100)
                {
                    boxes.push_back(new Box(j * BLOCK_WIDTH, i * BLOCK_HEIGHT));
                    board[i][j] = 2;
                }
            }
        }
    }
}

void Game::drawBoxes()
{
    for (int i = 0; i < static_cast<int>(boxes.size()); i++)
    {
        window->draw(*boxes[i]);
    }

}

void Game::drawBackground()
{
    window->clear();
}

void Game::drawInterface()
{
    interface->draw(*window, players);
}

void Game::drawPowerUps()
{
    for (int i = 0; i < static_cast<int>(powerUps.size()); i++)
    {
        window->draw(*powerUps[i]);
    }
}

void Game::getNewPowerUps()
{
    for (int i = 0; i < static_cast<int>((Box::powerUps).size()); i++)
    {
        powerUps.push_back(Box::powerUps[i]);
    }
    Box::powerUps.clear();
}

void Game::checkPowerUpPickUp()
{
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        Vector2i playerPos = players[i]->getCurrentBlock();
        for (int j = 0; j < static_cast<int>(powerUps.size()); j++)
        {
            Vector2i powerUpPos = transformToBlockPos(powerUps[j]->getPos());
            if (playerPos == powerUpPos)
            {
                powerUps[j]->givePower(players[i]);
                delete powerUps[j];
                powerUps.erase(powerUps.begin() + j);
            }
        }
    }
}

void Game::showGameOverScreen()
{
    RectangleShape background;
    background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    Color c = Color(150, 75, 50, 200);
    background.setFillColor(c);
    background.setPosition(0, 0);
    window->draw(background);

    Font font;
    font.loadFromFile("font/arial.ttf");
    Text text;
    text.setFont(font);
    text.setFillColor(Color(255, 255, 255));
    text.setCharacterSize(170);
    text.setPosition(WINDOW_WIDTH / 8, WINDOW_HEIGHT / 3);
    if (loser == 0)
    {
        text.setString("Goblin wins!");
    }
    else 
    {
        text.setString("Human wins!");
    }
    window->draw(text);
}

bool Game::getGameState()
{
    return isGameOver;
}