#ifndef WALL_h
#define WALL_h

#include "obstacle.hpp"

class Wall : public Obstacle {

    public:
        Wall(int id, float x, float y, float theta, int width, int height);

};

#endif