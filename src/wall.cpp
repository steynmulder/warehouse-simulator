#include "wall.hpp"

Wall::Wall(int id, float x, float y, float theta, int width, int height) : Obstacle::Obstacle(id, x, y, width, height, theta, Obstacle::Wall) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->theta = theta;
    this->width = width;
    this->height = height;

}