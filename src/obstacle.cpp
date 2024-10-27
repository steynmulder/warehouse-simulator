#include "obstacle.hpp"

#include <cmath>
#include <iostream>

using namespace std;

Obstacle::Obstacle(int id, float x, float y, int width, int height, float theta, Obstacle::ObstacleType type) {
    this-> id = id;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->theta = theta;
    this->type = type;
}

// we make the assumption that all obstacles are rectangles that can be rotated
bool Obstacle::isColliding(Obstacle &obs_ref) {

    Obstacle *obs = &obs_ref;
    vector<pair<float, float>> vertices_self = this->getVertices();
    vector<pair<float, float>> vertices_obs = obs->getVertices();

    
    for (int poly = 0; poly < 2; ++poly) {
        if (poly == 1) {
            vertices_self = obs->getVertices();
            vertices_obs = this->getVertices();
        }

        for (int i = 0; i < vertices_self.size(); ++i) {
            pair<float, float> current = vertices_self[i];
            pair<float, float> next = vertices_self[(i+1) % vertices_self.size()];

            pair<float, float> normal;
            normal.first = -(next.second - current.second);
            normal.second = next.first - current.first;

            float d = sqrtf(normal.first * normal.first + normal.second * normal.second);
            normal.first = normal.first / d;
            normal.second = normal.second / d;

            float min_proj_self = INFINITY;
            float max_proj_self = -INFINITY;
            for (int j = 0; j < vertices_self.size(); ++j) {
                float proj = vertices_self[j].first * normal.first + vertices_self[j].second * normal.second;
                min_proj_self = min(min_proj_self, proj);
                max_proj_self = max(max_proj_self, proj);
            }

            float min_proj_obs = INFINITY;
            float max_proj_obs = -INFINITY;
            for (int j = 0; j < vertices_obs.size(); ++j) {
                float proj = vertices_obs[j].first * normal.first + vertices_obs[j].second * normal.second;
                min_proj_obs = min(min_proj_obs, proj);
                max_proj_obs = max(max_proj_obs, proj);
            }

            if ((min_proj_self < min_proj_obs && max_proj_self < min_proj_obs) || (min_proj_obs < min_proj_self && max_proj_obs < min_proj_self)) {

                return false;
            }

        }
    }

    return true; 


}

vector<pair<float, float>> Obstacle::getVertices() {
    vector<pair<float, float>> result;

    float cx = this->x + this->width / 2.0;
    float cy = this->y + this->height / 2.0;

    float angle = this->theta * M_PI / 180.0;
    float cosA = cos(angle);
    float sinA = sin(angle);

    vector<pair<float, float>> corners = {
        {this->x - cx, this->y - cy},                 // Top-left
        {this->x + this->width - cx, this->y - cy},   // Top-right
        {this->x + this->width - cx, this->y + this->height - cy}, // Bottom-right
        {this->x - cx, this->y + this->height - cy}   // Bottom-left
    };

    for (pair<float, float> corner : corners) {
        float rotatedX = cx + (corner.first * cosA - corner.second * sinA);
        float rotatedY = cy + (corner.first * sinA + corner.second * cosA);
        result.push_back({rotatedX, rotatedY});
    }

    return result;
}