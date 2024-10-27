#include <iostream>
#include<vector>
#include <memory>

#include "simulation.hpp"
#include "robot.hpp"
#include "wall.hpp"
#include "obstacle.hpp"

using namespace std;


int main() {
    int WIDTH = 800;
    int OUTER_WALL_WIDTH = 15;

    vector<shared_ptr<Obstacle>> obstacles;

    obstacles.push_back(make_shared<Robot>(0, 500, 200, 0, 50, 50));
    obstacles.push_back(make_shared<Robot>(2, 50, 270, 45, 50, 50));

    
    obstacles.push_back(make_shared<Wall>(10, 0, 0, 0, WIDTH, OUTER_WALL_WIDTH));
    obstacles.push_back(make_shared<Wall>(11, 0, 0, 0, OUTER_WALL_WIDTH, WIDTH));
    obstacles.push_back(make_shared<Wall>(12, 0, (float) WIDTH - OUTER_WALL_WIDTH, 0, WIDTH, OUTER_WALL_WIDTH));
    obstacles.push_back(make_shared<Wall>(13, (float) WIDTH - OUTER_WALL_WIDTH, 0, 0, OUTER_WALL_WIDTH, WIDTH));

    obstacles.push_back(make_shared<Wall>(14, 400, 300, 23.987, 100, 39));

    
    simulate(WIDTH, obstacles);

    return 0;
}