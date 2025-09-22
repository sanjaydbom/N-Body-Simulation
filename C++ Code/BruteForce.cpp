#include "BruteForce.h"
#include <cmath>

BruteForce::BruteForce(std::vector<Particle>& p) : accel(p.size())
{
    particles = p;
    calculateAccelerations();
}

void BruteForce::calculateAccelerations()
{
    std::pair<float,float> zero_pair(0,0);
    std::fill(accel.begin(), accel.end(), zero_pair);
    float particle1[3];
    float particle2[3];
    float dx, dy, r, F, a1, a2, theta;
    for(int i = 0; i < particles.size(); i++)
    {
        for(int j = i+1; j < particles.size(); j++)
        {
            particles[i].get_pos(particle1);
            particles[j].get_pos(particle2);

            dx = particle2[0] - particle1[0]; // final - initial
            dy = particle2[1] - particle1[1];

            r = dx * dx + dy * dy;
            F = G / (r + 0.0001); //F = G * m1 * m2 / r, but I removed m1 and m2, because I need to multiply them
                                    //seperatly for each particles acceleration

            a1 = F * particles[j].get_mass();
            a2 = F * particles[i].get_mass();

            theta = atan2(dy, dx);

            accel[i].first += a1 * cos(theta);
            accel[i].second += a1 * sin(theta);
            accel[j].first -= a2 * cos(theta); //Newton's Third Law
            accel[j].second -= a2 * sin(theta); //Newton's Third Law
        }
    }
}

void BruteForce::updateVelocity()
{
    for(int i = 0; i < particles.size(); i++)
    {
        particles[i].update_velocity(accel[i].first * 0.5, accel[i].second * 0.5);
    }
}

void BruteForce::updatePosition()
{
    for(auto& p : particles)
    {
        p.update_pos();
    }
}

void BruteForce::step()
{
    updateVelocity();
    updatePosition();
    calculateAccelerations();
    updateVelocity();
}

void BruteForce::getPositions(float* pos_arr)
{
    for(int i = 0; i < particles.size(); i++)
    {
        particles[i].get_pos(pos_arr + 3 * i);
    }
}