#ifndef LIDAR_h
#define LIDAR_h

#include <unordered_set>
#include <memory>

#include "obstacle.hpp"

using namespace std;

class Lidar {

    private:
        int robot_id;
        float x;
        float y;
        int PRECISION = 36;

        pair<float, pair<float, float>> closest_distance(Obstacle obs, pair<float, float> pos, float angle);

    public:
        struct pair_hash {
            template <class T1, class T2>
            size_t operator()(const std::pair<T1, T2>& v) const {
                size_t hash1 = std::hash<T1>{}(v.first);
                size_t hash2 = std::hash<T2>{}(v.second);
                return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
                return hash1;
            }
        };


        Lidar(int id, float x, float y);
        int getId() {return this->robot_id;}
        float getX() {return this->x;}
        float getY() {return this->y;}
        void setPosition(float x, float y) {this->x = x; this-> y = y;}
        unordered_set<pair<float, float>, pair_hash> scan(vector<shared_ptr<Obstacle>> obstacles);

};

#endif