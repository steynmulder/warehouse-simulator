#include "simulation.hpp"
#include "robot.hpp"
#include "obstacle.hpp"
#include "wall.hpp"

#include<SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include<cmath>
#include <memory>
#include <unordered_map>

using namespace std;

float POINT_RADIUS = 4.0f;
int FPS = 60;

void simulate(int width, vector<shared_ptr<Obstacle>> obstacles) {
    sf::RenderWindow window(sf::VideoMode(width, width), "Warehouse Simulator");

    window.setFramerateLimit(FPS);

    // create robot rects
    unordered_map<int, sf::RectangleShape> robot_shapes;
    unordered_map<int, sf::RectangleShape> wall_shapes;
    unordered_map<int, sf::CircleShape> midpoints;
    unordered_map<int, sf::Text> ids;

    // load arial font for robot ids
    sf::Font font;
    if(!font.loadFromFile("../assets/fonts/arial.ttf")) {
        // TODO error
    }

    // create robot lidar pointclouds
    unordered_set<pair<float, float>, Lidar::pair_hash> lidar_points;

    for (const auto& obstacle : obstacles) {
        switch (obstacle->getType()) {
            case Obstacle::Robot:
            {
                // initialize robots
                sf::RectangleShape rect(obstacle->getSize());
                rect.setFillColor(sf::Color(
                    obstacle->getId() * 50,
                        200 - (obstacle->getId() * 50),
                        200 + (obstacle->getId() * 10),
                        255));
                robot_shapes[obstacle->getId()] = rect;

                // initialize midpoints
                sf::CircleShape point(POINT_RADIUS);
                point.setFillColor(sf::Color::White);
                midpoints[obstacle->getId()] = point;

                // initialize robot id
                sf::Text id;
                id.setFont(font);
                id.setString("id: " + to_string(obstacle->getId()));
                id.setCharacterSize(16);
                ids[obstacle->getId()] = id;
                break;
            }
            case Obstacle::Wall:
            {
                // initialize walls
                sf::RectangleShape rect(obstacle->getSize());
                rect.setFillColor(sf::Color(64, 64, 64));
                wall_shapes[obstacle->getId()] = rect;
                break;
            }
            default:
            {
                cout << "TODO default" << endl; // TODO
                break;
            }
        };
        
    }

    float alpha = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //updating
        for (int i = 0; i < obstacles.size(); ++i) {
            switch (obstacles[i]->getType()) {
                case Obstacle::Robot:
                {
                    Robot* robot = dynamic_cast<Robot*>(obstacles[i].get());
                    if (robot) {
                        bool colliding = false;
                        for (const auto& obs : obstacles) {
                            if (robot->getId() != obs->getId()) {
                                if (robot->isColliding(*obs)) {
                                    colliding = true;
                                    break;
                                }
                            }
                            
                        }

                        if (!colliding) {
                            cout << alpha << endl;
                            robot->move({cosf(alpha), powf(-1, i+1) * sinf(alpha)});
                            // robot->rotate();
                        }

                        // scanning
                        if (robot->getId() == 0) {
                            unordered_set<pair<float, float>, Lidar::pair_hash> points = robot->getLidar().scan(obstacles);
                            lidar_points.insert(points.begin(), points.end());
                        }
                    } else {
                        // TODO error
                    }
                    break;
                    
                }
                default:
                {
                    //TODO error
                    break;
                }
            };
            
        }
        alpha += 0.05;
        if (alpha > M_2_PI) {alpha = 0;}


        // drawing
        window.clear(sf::Color(255, 248, 226));
        for (const auto& obstacle : obstacles) {
            switch (obstacle->getType()) {
                case Obstacle::Robot:
                {
                    Robot* robot = dynamic_cast<Robot*>(obstacle.get());
                    if (robot) {
                        // draw robot
                        sf::RectangleShape rect = robot_shapes[robot->getId()];
                        
                        int a = (rect.getPosition().x + rect.getSize().x / 2);
                        int b = (rect.getPosition().y + rect.getSize().y / 2);
                        rect.setOrigin(a, b);
                        
                        rect.setPosition(robot->getPosition());
                        // rotation in this function is in clockwise direction, we want counterclockwise
                        rect.setRotation(robot->getTheta());
                        rect.setPosition(rect.getPosition().x + rect.getOrigin().x, rect.getPosition().y + rect.getOrigin().y);
                        
                        window.draw(rect);

                        // draw midpoint of robot
                        sf::CircleShape point = midpoints[robot->getId()];
                        point.setFillColor(sf::Color::Green);
                        float cx = robot->getPosition().x + robot->getSize().x / 2 - POINT_RADIUS / 2;
                        float cy = robot->getPosition().y + robot->getSize().y / 2 - POINT_RADIUS / 2;
                        point.setPosition(cx, cy);
                        window.draw(point);


                        // draw robot id
                        sf::Text id = ids[robot->getId()];
                        sf::FloatRect id_bounds = id.getLocalBounds();
                        id.setPosition(sf::Vector2f(
                            robot->getPosition().x + robot->getSize().x / 2 - id_bounds.width / 2,
                            robot->getPosition().y + robot->getSize().y / 2 + id_bounds.height / 2));
                        window.draw(id);
                    } else {
                        // TODO error
                    }
                    break;
                    
                }
                case Obstacle::Wall:
                {
                    Wall* wall = dynamic_cast<Wall*>(obstacle.get());
                    if (wall) {
                        sf::RectangleShape rect = wall_shapes[wall->getId()];

                        int a = (rect.getPosition().x + rect.getSize().x / 2);
                        int b = (rect.getPosition().y + rect.getSize().y / 2);
                        rect.setOrigin(a, b);
                        
                        rect.setPosition(wall->getPosition());
                        // rotation in this function is in clockwise direction, we want counterclockwise
                        rect.setRotation(wall->getTheta());
                        rect.setPosition(rect.getPosition().x + rect.getOrigin().x, rect.getPosition().y + rect.getOrigin().y);
                        
                        window.draw(rect);
                    } else {
                        // TODO error
                    }
                    break;
                    
                }
                default:
                {
                    // TODO error
                    break;
                }
            };
            
        }

        for (pair<float, float> coord : lidar_points) {
            sf::CircleShape p(5.0f);
            p.setFillColor(sf::Color(255, 0, 0, 128));
            p.setPosition(sf::Vector2f(coord.first, coord.second));
            window.draw(p);
        }

        cout << lidar_points.size() << endl;

        window.display();
    }

}