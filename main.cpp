#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <cmath>
#include <time.h>
#include "paddle.h"
#include "ball.h"

std::string int_to_string(int i);

///MAIN
int main()
{
    int x = 800;
    int y = 600;
    // create the window

    sf::RenderWindow window(sf::VideoMode(x, y), "PONG", sf::Style::Close);

    sf::Font font;
    font.loadFromFile("consola.ttf");

    bool start = true;
    bool win = false;
    float mrate = .05;
    int winCon = 10;

    sf::Text startText;
    startText.setFont(font);
    startText.setCharacterSize(x/40);
    startText.setFillColor(sf::Color::White);
    startText.setString("Use W/S and I/K to move paddles.\n\tPress any key to begin.");
    startText.setPosition(sf::Vector2f((x/2)-(x/4.6),(y/4)));

    sf::Text endText;
    endText.setFont(font);
    endText.setCharacterSize(x/40);
    endText.setFillColor(sf::Color::White);
    endText.setPosition(sf::Vector2f((x/2)-(x/6),(y/4)));
    //p2Score.setString("");

    int p1score = 0;
    int p2score = 0;

    sf::Text p1Score;
    p1Score.setFont(font);
    p1Score.setCharacterSize(x/20);
    p1Score.setFillColor(sf::Color::White);

    sf::Text p2Score;
    p2Score.setFont(font);
    p2Score.setCharacterSize(x/20);
    p2Score.setFillColor(sf::Color::White);

    p1Score.setPosition(sf::Vector2f((x/2)-(x/4),y/100));
    p2Score.setPosition(sf::Vector2f((x/2)+(x/4),y/100));

    std::vector<sf::RectangleShape> net;
    for(int k = 0; k < y/10; k++){
        sf::RectangleShape dot;
        dot.setFillColor(sf::Color::White);
        dot.setSize(sf::Vector2f(x/200,y/200));
        dot.setPosition(sf::Vector2f(x/2-x/400,k*10));
        net.push_back(dot);
    }

    int paddleWidth = x/80;
    int paddleHeight = y/10;
    Paddle p1Paddle(sf::Vector2f(x/40,y/2-paddleHeight/2), sf::Vector2f(paddleWidth,paddleHeight));
    Paddle p2Paddle(sf::Vector2f(x-x/40-paddleWidth,y/2-paddleHeight/2), sf::Vector2f(paddleWidth,paddleHeight));

    sf::Keyboard::Key p1up = sf::Keyboard::W;
    sf::Keyboard::Key p1down = sf::Keyboard::S;

    sf::Keyboard::Key p2up = sf::Keyboard::I;
    sf::Keyboard::Key p2down = sf::Keyboard::K;


    float brate = mrate*2.0;
    Ball ball(sf::Vector2f(x/2-paddleWidth/2,y/2-paddleWidth/2),sf::Vector2f(paddleWidth,paddleWidth));
    ball.applyVector(sf::Vector2f(brate,0));

    sf::FloatRect winbCeil(0,0,x,1);
    sf::FloatRect winbFloor(0,y,x,1);
    sf::FloatRect winbRwall(x,0,1,y);
    sf::FloatRect winbLwall(0,0,1,y);

    window.clear(sf::Color::Black);
    window.display();
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            //std::cout << "polling... #" << pollingVal << std::endl;
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
                std::cout << "Closed Caught!" << std::endl;
            }
            if (event.type == sf::Event::KeyPressed){
                std::cout << "KeyPressed Caught!" << std::endl;
                start = false;
                float prate = 1/mrate;
                if(sf::Keyboard::isKeyPressed(p1up) && !p1Paddle.collision(winbCeil)){
                    p1Paddle.movePaddle(-prate);
                } else if(sf::Keyboard::isKeyPressed(p1down) && !p1Paddle.collision(winbFloor)){
                    p1Paddle.movePaddle(prate);
                }
                if(sf::Keyboard::isKeyPressed(p2up) && !p2Paddle.collision(winbCeil)){
                    p2Paddle.movePaddle(-prate);
                } else if(sf::Keyboard::isKeyPressed(p2down) && !p2Paddle.collision(winbFloor)){
                    p2Paddle.movePaddle(prate);
                }
                /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && win){
                    start = true;
                    win = false;
                }*/
            }
        }

        /// Ball Movement
        if(!start && !win){
            ball.step();
            if(ball.collision(winbCeil) || ball.collision(winbFloor)){
                ball.reflectVector(false,true);
            }
            Ball nball(sf::Vector2f(x/2-paddleWidth/2,y/2-paddleWidth/2),sf::Vector2f(paddleWidth,paddleWidth));
            if(ball.collision(winbRwall)){
                p1score++;
                nball.applyVector(sf::Vector2f(-brate,0));
                ball = nball;
                //delete nball;
            }
            if(ball.collision(winbLwall)){
                p2score++;
                nball.applyVector(sf::Vector2f(brate,0));
                ball = nball;
                //delete nball;
            }
            if(ball.collision(p1Paddle.getBounds())){
                if(ball.getVector().y == 0){
                    ball.applyVector(sf::Vector2f(0,brate));
                }
                ball.reflectVector(true,p1Paddle.getPosition().y > y/2);
            }
            if(ball.collision(p2Paddle.getBounds())){
                if(ball.getVector().y == 0){
                    ball.applyVector(sf::Vector2f(0,-brate));
                }
                ball.reflectVector(true,p2Paddle.getPosition().y > y/2);
            }
        }
        if(win = (p1score == winCon)){
            endText.setString("\tPlayer 1 Wins!"/*\nPress SPACE to play again."*/);
        } else if(win = (p2score == winCon)){
            endText.setString("\tPlayer 2 Wins!"/*\nPress SPACE to play again."*/);
        }


        // clear the window
        window.clear(sf::Color::Black);
        // draw everything here...
        p1Score.setString(int_to_string(p1score));
        window.draw(p1Score);
        p2Score.setString(int_to_string(p2score));
        window.draw(p2Score);

        p1Paddle.draw(&window);
        p2Paddle.draw(&window);
        ball.draw(&window);

        for(int k = 0; k < net.size(); k++){
            window.draw(net[k]);
        }

        if(start){
            window.draw(startText);
        }

        if(win && !start){
            window.draw(endText);
        }

        window.display();
    }

    return 0;

}

std::string int_to_string(int i){
    std::stringstream ss;
    ss << i;
    return ss.str();
}
