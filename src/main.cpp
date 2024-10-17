#include <iostream>
#include<vector>

#include "graphics.hpp"
#include "robot.hpp"

using namespace std;


int main() {
    int WIDTH = 800;

    Robot robot1(0, 200, 200, 0, 50, 50);
    // Robot robot2(1, 100, 600, 45, 50, 50);
    Robot robot3(2, 100, 200, 25, 50, 50);

    vector<Robot> robots;

    robots.push_back(robot1);
    // robots.push_back(robot2);
    robots.push_back(robot3);

    
    draw(WIDTH, robots);

    return 0;
}