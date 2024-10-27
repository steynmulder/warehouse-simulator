#ifndef OBSTACLE_h
#define OBSTACLE_h

#include "SFML/Graphics.hpp"

class Obstacle {
    public:
        enum ObstacleType {
            Wall,
            Shelf,
            Robot
        };

    protected:
        int id;
        float x;
        float y;
        int width;
        int height;
        float theta;
        ObstacleType type;

    public:
        Obstacle(int id, float x, float y, int width, int height, float theta, ObstacleType obs_type);
        virtual ~Obstacle() = default;
        int getId() {return id;}
        sf::Vector2f getPosition() {return sf::Vector2f(x, y);};
        sf::Vector2f getSize() {return sf::Vector2f(width, height);};
        float getTheta() {return this->theta;}
        ObstacleType getType() {return this->type;};
        void setPosition(sf::Vector2f pos) {this->x = pos.x; this->y = pos.y;}
        void setX(float x) {this->x = x;}
        void setY(float y) {this->y = y;}
        void setTheta(float theta) {this->theta = theta;}
        void setSize(std::vector<int> size) {this->width = size[0];
                                        this->height = size[1];}

        bool isColliding(Obstacle&);
        std::vector<std::pair<float, float>> getVertices();

};

#endif