#include "paddle.h"

Paddle::Paddle(sf::Vector2f pos, sf::Vector2f siz){
    paddle.setPosition(pos);
    paddle.setSize(siz);
    paddle.setFillColor(sf::Color::White);
}

bool Paddle::collision(sf::FloatRect ball){
    return paddle.getGlobalBounds().intersects(ball);
}

sf::FloatRect Paddle::getBounds(){
    return paddle.getGlobalBounds();
}

sf::Vector2f Paddle::getPosition(){
    return paddle.getPosition();
}

void Paddle::movePaddle(int y){
    paddle.move(0,y);
}

void Paddle::draw(sf::RenderWindow* win){
    win->draw(paddle);
}
