#include "ball.h"

Ball::Ball(sf::Vector2f pos, sf::Vector2f siz){
    ball.setPosition(pos);
    ball.setSize(siz);
    ball.setFillColor(sf::Color::White);

    movVec = sf::Vector2f(0,0);
}

bool Ball::collision(sf::FloatRect paddle){
    return ball.getGlobalBounds().intersects(paddle);
}

void Ball::draw(sf::RenderWindow* win){
    win->draw(ball);
}

void Ball::applyVector(sf::Vector2f vec){
    movVec = sf::Vector2f(movVec.x+vec.x,movVec.y+vec.y);
}

sf::Vector2f Ball::getVector(){
    return movVec;
}

void Ball::reflectVector(bool x_axis, bool y_axis){
    int x_reflect = x_axis ? -1 : 1;
    int y_reflect = y_axis ? -1 : 1;
    movVec = sf::Vector2f(x_reflect*movVec.x,y_reflect*movVec.y);
}

void Ball::step(){
    ball.move(movVec);
}

void Ball::setPosition(sf::Vector2f pos){
    ball.setPosition(pos);
}
