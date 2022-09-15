#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Solver.hpp"
#include "Global.hpp"

using namespace sf;


int main()
{
    Solver solver;

    Objects.reserve(10);
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "Hello World", sf::Style::Default, settings);

    View view;
    view.setCenter(0, 0);
    view.setSize(800, 600);

    window.setView(view);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::Clock deltaClock;   

    RectangleShape Square = RectangleShape(solver.squareConstraint);
    Square.setFillColor(Color::Black);
    Square.setOrigin(solver.squareConstraint / 2.f);


    CircleShape Circle = CircleShape(solver.circleConstraint, 80);
    Circle.setFillColor(Color::Black);
    Circle.setOrigin({ solver.circleConstraint, solver.circleConstraint });

    CircleShape shape = CircleShape(10.f);
    

    while (window.isOpen())
    {

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                // 5.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (15.f - 5.f)))
                Objects.push_back({ ((Vector2f)Mouse::getPosition(window)) - ((Vector2f)window.getSize() / 2.0f), 10, Color(rand() % 256, rand() % 256, rand() % 256) });
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::C) {
                    Objects.clear();
                }
            }

        }
            
        window.clear(Color(150, 150, 150));
        window.draw(Square);


        solver.Update();


        for (Object& obj : Objects)
        {
            shape.setPosition(obj.position);
            shape.setRadius(obj.radius);
            shape.setOrigin({ obj.radius, obj.radius });
            shape.setFillColor(obj.color);

            window.draw(shape);
        }


        window.display();
        Time dtC = deltaClock.restart();
        dt = dtC.asSeconds();
    }
    

    return 0;
}
