#include "lidar.hpp"

#include <cmath>
#include <iostream>

using namespace std;


Lidar::Lidar(int id, float x, float y) {
    this->robot_id = id;
    this->x = x;
    this->y = y;
}

unordered_set<pair<float, float>, Lidar::pair_hash> Lidar::scan(vector<shared_ptr<Obstacle>> obstacles) {
    unordered_set<pair<float, float>, Lidar::pair_hash> result;

    for (int i = 0; i < this->PRECISION; ++i) {
        float angle = (360.0f / this->PRECISION) * i * M_PI / 180; // radians
        float d = INFINITY;
        pair<float, float> best = {INFINITY, INFINITY};
        for (const auto& obs : obstacles) {
            if (this->getId() != obs->getId()) { // obstacle is not robot where lidar is mounted on

                pair<float, pair<float, float>> res = closest_distance(*obs.get(), {this->x, this->y}, angle);
                float dist = res.first;
                if (dist < d) {
                    d = dist;
                    best.first = res.second.first;
                    best.second = res.second.second;
                }
            }
            
        }
        result.insert(best);
    }

    return result;
}

pair<float, pair<float, float>> Lidar::closest_distance(Obstacle obs, pair<float, float> pos, float angle) {
    vector<pair<float, float>> vertices = obs.getVertices();
    float min_dist = INFINITY;
    pair<float, float> min_point = {INFINITY, INFINITY};
    for (int i = 0; i < vertices.size(); ++i) {
        pair<float, float> current = vertices[i];
        pair<float, float> next = vertices[(i+1) % vertices.size()];

        pair<float, float> dir;
        dir.first = cosf(angle);
        dir.second = sinf(angle);

        float det = dir.first * (next.second - current.second) - dir.second * (next.first - current.first);
        if (abs(det) < 1e-9) {
            continue;
        }

        float t = ((current.first - pos.first) * (next.second - current.second) - (current.second - pos.second) * (next.first - current.first)) / det;
        float s = ((current.first - pos.first) * dir.second - (current.second - pos.second) * dir.first) / det;

        if (t >= 0 && s >= 0 && s <= 1) {
            pair<float, float> point = {dir.first * t + pos.first, dir.second * t + pos.second};
            float dist = sqrtf(powf(point.first - pos.first, 2) + powf(point.second - pos.second, 2));

            if (dist < min_dist) {
                min_dist = dist;
                min_point = point;
            }
        }

    }

    return {min_dist, min_point};
}