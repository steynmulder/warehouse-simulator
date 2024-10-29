#include "robot.hpp"

#include <vector>
#include <iostream>

using namespace std;

Robot::Robot(int id, float x, float y, float theta, int width, int height) : Obstacle::Obstacle(id, x, y, width, height, theta, Obstacle::Robot), lidar(id, x, y) {

    this->id = id;
    this->x =x ;
    this->y = y;
    this->theta = theta;
    this->width = width;
    this->height = height;
}

void Robot::move(vector<float> move) {
    Robot::setX(Robot::getPosition().x + move[0]);
    Robot::setY(Robot::getPosition().y + move[1]);

    this->lidar.setPosition(this->x + this->width/2, this->y + this->height/2);
}

void Robot::rotate(float angle) {
    Robot::setTheta(Robot::getTheta() + angle);
}