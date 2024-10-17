#include "robot.hpp"

#include <vector>
#include <iostream>

using namespace std;

Robot::Robot(int id, float x, float y, float theta, int width, int length) {
    this->id = id;
    this->x =x ;
    this->y = y;
    this->theta = theta;
    this->width = width;
    this->length = length;
}

void Robot::move(vector<float> move) {
    Robot::setX(Robot::getPosition().x + move[0]);
    Robot::setY(Robot::getPosition().y + move[1]);
}

void Robot::rotate(float angle) {
    Robot::setTheta(Robot::getTheta() + angle);
}