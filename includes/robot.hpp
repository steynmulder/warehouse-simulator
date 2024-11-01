#ifndef ROBOT_h
#define ROBOT_h

#include "obstacle.hpp"
#include <vector>
#include<SFML/Graphics.hpp>

class Robot : public Obstacle {
    public:
        Robot(int id, float x, float y, float theta, int width, int height);

        void move(std::vector<float>);
        void rotate(float);
        
};

#endif