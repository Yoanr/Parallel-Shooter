#include "parallel-shooter.h"
#include <iostream>
#include <cmath>

void InitGame(App &app)
{
    DisplayableObject *blackPlayer = new DisplayableObject("img/black-player.png");
    DisplayableObject *whitePlayer = new DisplayableObject("img/white-player.png");
    DisplayableObject *blackBackground = new DisplayableObject("img/black-background.png");
    DisplayableObject *whiteBackground = new DisplayableObject("img/white-background.png");

    initBlackPlayer(blackPlayer);
    initWhitePlayer(whitePlayer);
    initBlackBackground(blackBackground);
    initWhiteBackground(whiteBackground);
    initEnnemies(app, blackPlayer, whitePlayer);
  
    blackPlayer->setFunction(&blackPlayerMovement);

    whitePlayer->setFunction(&whitePlayerMovement);

    app.addObjectTo(blackBackground, GAME_SCENE);
    app.addObjectTo(whiteBackground, GAME_SCENE);
    app.addObjectTo(blackPlayer, GAME_SCENE);
    app.addObjectTo(whitePlayer, GAME_SCENE);
    
}

void initBlackPlayer(DisplayableObject *blackPlayer)
{
    sf::Vector2f position = {1390.0f, 490.0f};
    sf::Vector2f origin = {50.0f, 50.0f};
    sf::Vector2f scale = {0.3f, 0.3f};

    blackPlayer->setPosition(position);
    blackPlayer->setOrigin(origin);
    blackPlayer->setScale(scale);
    blackPlayer->setAngle(0.0f);
}

void initWhitePlayer(DisplayableObject *whitePlayer)
{
    sf::Vector2f position = {430.0f, 490.0f};
    sf::Vector2f origin = {50.0f, 50.0f};
    sf::Vector2f scale = {0.3f, 0.3f};

    whitePlayer->setPosition(position);
    whitePlayer->setOrigin(origin);
    whitePlayer->setScale(scale);
    whitePlayer->setAngle(0.0f);
}

void initWhiteBackground(DisplayableObject *whiteBackground)
{
    sf::Vector2f position = {960.0f, 0.0f};

    whiteBackground->setPosition(position);
}

void whitePlayerMovement(GameObject *self)
{
    sf::Vector2f position = self->getPosition();
    sf::Vector2f vector = {0.0f, 0.0f};

    // Calculate the vector based on angle of black player
    vector.x = sin(static_cast<DisplayableObject *>(self)->getAngle() * 3.1415 / 180.0f);
    vector.y = cos(static_cast<DisplayableObject *>(self)->getAngle() * 3.1415 / 180.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        position.y -= self->getSpeed() * vector.y;
        position.x -= self->getSpeed() * vector.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        position.y += self->getSpeed() * vector.y;
        position.x += self->getSpeed() * vector.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        static_cast<DisplayableObject *>(self)->setAngle(static_cast<DisplayableObject *>(self)->getAngle() + ROTATE_SPEED);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        static_cast<DisplayableObject *>(self)->setAngle(static_cast<DisplayableObject *>(self)->getAngle() - ROTATE_SPEED);
    position.y = (position.y < 0.0f) ? 0.0f : (position.y > 1080.0f) ? 1080.0f : position.y;
    static_cast<DisplayableObject *>(self)->setPosition(position);
}


void initBlackBackground(DisplayableObject *blackBackground)
{
    sf::Vector2f position = {0.0f, 0.0f};

    blackBackground->setPosition(position);
}

void blackPlayerMovement(GameObject *self)
{
    sf::Vector2f position = self->getPosition();
    sf::Vector2f vector = {0.0f, 0.0f};

    // Calculate the vector based on angle of black player
    vector.x = - sin(static_cast<DisplayableObject *>(self)->getAngle() * 3.1415 / 180.0f);
    vector.y = cos(static_cast<DisplayableObject *>(self)->getAngle() * 3.1415 / 180.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        position.y -= self->getSpeed() * vector.y;
        position.x -= self->getSpeed() * vector.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        position.y += self->getSpeed() * vector.y;
        position.x += self->getSpeed() * vector.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        static_cast<DisplayableObject *>(self)->setAngle(static_cast<DisplayableObject *>(self)->getAngle() + ROTATE_SPEED);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        static_cast<DisplayableObject *>(self)->setAngle(static_cast<DisplayableObject *>(self)->getAngle() - ROTATE_SPEED);
    position.y = (position.y < 0.0f) ? 0.0f : (position.y > 1080.0f) ? 1080.0f : position.y;
    static_cast<DisplayableObject *>(self)->setPosition(position);
}

void initEnnemies(App &app, DisplayableObject *blackPlayer, DisplayableObject *whitePlayer)
{
    float randX = 0.0f;
    float randY = 0.0f;

    // 10 levels of ennemies 10 + the level per level
    // Generate white ennemies (left of the screen)
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10 + i; j++)
        {
            randX = rand() % 50 - 50;
            randY = (randX < -25.0f) ? rand() % 50 - 75 : rand() % 50 + 1125.0f;
            DisplayableObject *ennemy = new DisplayableObject("img/whiteEnnemy.png");
            sf::Vector2f position = {randX, randY};
            sf::Vector2f origin = {50.0f, 50.0f};
            sf::Vector2f scale = {0.3f, 0.3f};

            ennemy->setPosition(position);
            ennemy->setOrigin(origin);
            ennemy->setScale(scale);
            ennemy->setAngle(0.0f);
            ennemy->addObject(blackPlayer);
            ennemy->setTag("ennemy_white_" + std::to_string(i + 1));
            if (i > 0)
                ennemy->setActive(false);
            ennemy->setFunction(&ennemyMovement);
            app.addObjectTo(ennemy, GAME_SCENE);
        }
    }
    // Generate black ennemies (right of the screen)
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10 + i; j++)
        {
            randX = rand() % 50 + 1945;
            randY = (randX > 1970.0f) ? rand() % 50 - 75 : rand() % 50 + 1125.0f;
            DisplayableObject *ennemy = new DisplayableObject("img/blackEnnemy.png");
            sf::Vector2f position = {randX, randY};
            sf::Vector2f origin = {50.0f, 50.0f};
            sf::Vector2f scale = {0.3f, 0.3f};

            ennemy->setPosition(position);
            ennemy->setOrigin(origin);
            ennemy->setScale(scale);
            ennemy->setAngle(0.0f);
            ennemy->addObject(whitePlayer);
            ennemy->setTag("ennemy_black_" + std::to_string(i + 1));
            if (i > 0)
                ennemy->setActive(false);
            ennemy->setFunction(&ennemyMovement);
            app.addObjectTo(ennemy, GAME_SCENE);
        }
    }
}

void ennemyMovement(GameObject *self)
{
    sf::Vector2f targetPosition = static_cast<DisplayableObject *>(self)->getObjects()[0]->getPosition();
    sf::Vector2f position = self->getPosition();

    if (position.x > targetPosition.x)
        position.x -= self->getSpeed();
    else
        position.x += self->getSpeed();
    if (position.y > targetPosition.y)
        position.y -= self->getSpeed();
    else
        position.y += self->getSpeed();
    static_cast<DisplayableObject *>(self)->setPosition(position);
}
