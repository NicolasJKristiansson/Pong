#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>

class Paddle{
private:
    sf::RectangleShape paddle;

public:
    Paddle(sf::Vector2f,sf::Vector2f);

    bool collision(sf::FloatRect);
    void movePaddle(int);
    void draw(sf::RenderWindow*);
};

#endif
