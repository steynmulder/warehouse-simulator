#ifndef ROBOT_h
#define ROBOT_h

#include <vector>
#include<SFML/Graphics.hpp>

class Robot {
    int id;
    float x;
    float y;
    float theta;
    int width;
    int length;

    public:
        Robot(int id, float x, float y, float theta, int width, int length);

        void move(std::vector<float>);
        void rotate(float);

        // getters and setters
        int getId() {return id;}
        sf::Vector2f getPosition() {return sf::Vector2f(x, y);}
        float getTheta() {return theta;}
        sf::Vector2f getSize() {
            sf::Vector2f size;
            size.x = this->width;
            size.y = this->length;
            return size;
        }

        void setX(float x) {this->x = x;}
        void setY(float y) {this->y = y;}
        void setTheta(float theta) {this->theta = theta;}
        void setSize(std::vector<int> size) {this->width = size[0];
                                        this->length = size[1];}
};

#endif