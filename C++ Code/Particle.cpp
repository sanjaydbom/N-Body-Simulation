#include "Particle.h"

Particle::Particle(float mass_, float x_pos_, float y_pos_, float radius_, float vel_x_, float vel_y_)
{
    mass = mass_;
    x_pos = x_pos_;
    y_pos = y_pos_;
    z_pos = 0.0;
    radius = radius_;
    vel_x = vel_x_;
    vel_y = vel_y_;
}

void Particle::get_pos(float* pos)
{
    pos[0] = x_pos;
    pos[1] = y_pos;
    pos[2] = 0.0;
}

void Particle::update_pos()
{
    x_pos += vel_x;
    y_pos += vel_y;
}

void Particle::update_velocity(float dvel_x, float dvel_y)
{
    vel_x += dvel_x;
    vel_y += dvel_y;
}

float Particle::get_mass()
{
    return mass;
}

float Particle::get_radius()
{
    return radius;
}

void Particle::get_velocity(float* array)
{
    array[0] = vel_x;
    array[1] = vel_y;
    array[2] = 0.0;
}