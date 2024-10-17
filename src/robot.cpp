#include "robot.hpp"

#include <vector>

using namespace std;

Robot::Robot(int id, float x, float y, float theta, int width, int length) {
    this->id = id;
    this->x =x ;
    this->y = y;
    this->theta = theta;
    this->width = width;
    this->length = length;
}


// TODO make smooth movement
void Robot::move(vector<float> move) {
    // Robot::setX(Robot::getX() + move[0]);
    // Robot::setY(Robot::getY() + move[1]);
}