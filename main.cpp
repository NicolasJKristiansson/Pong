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

    sf::Text p1Score;
    p1Score.setFont(font);
    p1Score.setCharacterSize(x/20);
    p1Score.setFillColor(sf::Color::White);
    p1Score.setString(int_to_string(0));

    sf::Text p2Score;
    p2Score.setFont(font);
    p2Score.setCharacterSize(x/20);
    p2Score.setFillColor(sf::Color::White);
    p2Score.setString(int_to_string(0));

    p1Score.setPosition(sf::Vector2f((x/2)-(x/4),y/100));
    p2Score.setPosition(sf::Vector2f((x/2)+(x/4),y/100));

    std::vector<sf::RectangleShape> net;
    for(int k = 0; k < y/10; k++){
        sf::RectangleShape dot;
        dot.setFillColor(sf::Color::White);
        dot.setSize(sf::Vector2f(x/200,y/200));
        dot.setPosition(sf::Vector2f(x/2,k*10));
        net.push_back(dot);
    }









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
            }
        }

        // clear the window
        window.clear(sf::Color::Black);
        // draw everything here...
        window.draw(p1Score);
        window.draw(p2Score);

        for(int k = 0; k < net.size(); k++){
            window.draw(net[k]);
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