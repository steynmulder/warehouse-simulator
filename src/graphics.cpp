#include "graphics.hpp"
#include "robot.hpp"

#include<SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

float POINT_RADIUS = 4.0f;
int FPS = 60;

void draw(int width, vector<Robot> robots) {
    sf::RenderWindow window(sf::VideoMode(width, width), "Warehouse Simulator");

    window.setFramerateLimit(FPS);

    // create robot rects
    vector<sf::RectangleShape> robot_shapes;
    vector<sf::CircleShape> midpoints;
    vector<sf::Text> ids;

    // load arial font for robot ids
    sf::Font font;
    if(!font.loadFromFile("../assets/fonts/arial.ttf")) {
        // TODO error
    }

    for (Robot& robot : robots) {
        // initialize robots
        sf::RectangleShape rect(robot.getSize());
        rect.setFillColor(sf::Color(
            robot.getId() * 50,
                200 - (robot.getId() * 50),
                200 + (robot.getId() * 10),
                255));
        robot_shapes.push_back(rect);

        // initialize midpoints
        sf::CircleShape point(POINT_RADIUS);
        point.setFillColor(sf::Color::White);
        midpoints.push_back(point);

        // initialize robot id
        sf::Text id;
        id.setFont(font);
        id.setString("id: " + to_string(robot.getId()));
        id.setCharacterSize(16);
        ids.push_back(id);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int i = 0; i < robots.size(); ++i) {
            // draw robot
            sf::RectangleShape rect = robot_shapes[i];
            Robot robot = robots[i];
            
            int a = (rect.getPosition().x + rect.getSize().x / 2);
            int b = (rect.getPosition().y + rect.getSize().y / 2);
            rect.setOrigin(a, b);
            
            rect.setPosition(robot.getPosition());
            rect.setRotation(robot.getTheta());
            rect.setPosition(rect.getPosition().x + rect.getOrigin().x, rect.getPosition().y + rect.getOrigin().y);
            
            window.draw(rect);

            // draw midpoint of robot
            sf::CircleShape point = midpoints[i];
            point.setPosition(sf::Vector2f(
                robot.getPosition().x + robot.getSize().x / 2 - POINT_RADIUS,
                robot.getPosition().y + robot.getSize().y / 2 - POINT_RADIUS));
            window.draw(point);

            // draw robot id
            sf::Text id = ids[i];
            sf::FloatRect id_bounds = id.getLocalBounds();
            id.setPosition(sf::Vector2f(
                robot.getPosition().x + robot.getSize().x / 2 - id_bounds.width / 2,
                robot.getPosition().y + robot.getSize().y / 2 + id_bounds.height / 2));
            window.draw(id);
        }

        window.display();
    }

}