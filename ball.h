#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>

class Ball{
private:
    sf::RectangleShape ball;
    sf::Vector2f movVec;

public:
    Ball(sf::Vector2f,sf::Vector2f);

    bool collision(sf::FloatRect);
    void draw(sf::RenderWindow*);
    void applyVector(sf::Vector2f);
    sf::Vector2f getVector();
    void reflectVector(bool,bool);
    void step();
    void setPosition(sf::Vector2f);
};

#endif
