#ifndef PARTICLE_H
#define PARTICLE_H

#include <cstdlib>
#include <utility>

class Particle{
public:
    Particle(float mass_, float x_pos_, float y_pos_, float radius_, float vel_x_, float vel_y_);
    std::pair<float, float> get_pos();
    void update_pos();
    void update_velocity(float dvel_x, float dvel_y);
    float get_mass();

private:
    float mass;
    float x_pos;
    float y_pos;
    float radius;
    float vel_x;
    float vel_y;
};

#endif