#include "BruteForce.h"
#include "Constants.h"
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

            //std::cout << particle1[0] << " " << particle1[1] << "\n";
            //std::cout << particle2[0] << " " << particle2[1] << "\n";

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
            //std::cout << accel[i].first << " " << accel[i].second << "\n";
            //std::cout << accel[j].first << " " << accel[j].second << "\n";
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
    checkCollisions();
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
        pos_arr[3 * i + 0] /= (X_LENGTH / 2);
        pos_arr[3 * i + 1] /= (Y_LENGTH / 2);
    }
}

void BruteForce::checkCollisions()
{
    float particle1[3];
    float particle2[3];
    bool changed = false;
    for(int i = 0; i < particles.size(); i++)
    {
        for(int j = i+1; j < particles.size(); j++)
        {
            particles[i].get_pos(particle1);
            particles[j].get_pos(particle2);

            if(std::pow(particle2[0] - particle1[0], 2) + std::pow(particle2[1] - particle1[1], 2) <= std::pow(particles[j].get_radius() + particles[i].get_radius(), 2))
            {
                changed = true;

                std::cout << "Collided!\n";

                float newBasisVectorI[3] = {0.0, 0.0, 0.0};
                float newBasisVectorJ[3] = {0.0, 0.0, 0.0};

                float V1_I[3];
                float V2_I[3];

                particles[i].get_velocity(V1_I);
                particles[j].get_velocity(V2_I);
                
                //change coordinate system so that the 2 particles collide only on the x-axis
                newBasisVectorI[0] = particle2[0] - particle1[0];
                newBasisVectorI[1] = particle2[1] - particle1[1];

                //normalize
                float size = std::pow(std::pow(newBasisVectorI[0], 2) + std::pow(newBasisVectorI[1], 2), 0.5);

                newBasisVectorI[0] /= size;
                newBasisVectorI[1] /= size;
                
                //get orthogonal vector for y axis
                newBasisVectorJ[0] = -1 * newBasisVectorI[1];
                newBasisVectorJ[1] = newBasisVectorI[0];

                float NEW_V1_X_I = dot_product(newBasisVectorI, V1_I);
                float NEW_V2_X_I = dot_product(newBasisVectorI, V2_I);

                float NEW_V1_Y = dot_product(newBasisVectorJ, V1_I);
                float NEW_V2_Y = dot_product(newBasisVectorJ, V2_I);

                float NEW_V1_X_F = (particles[i].get_mass() - particles[j].get_mass()) * NEW_V1_X_I + 2 * particles[j].get_mass() * NEW_V2_X_I / (particles[i].get_mass() + particles[j].get_mass());
                float NEW_V2_X_F = (particles[j].get_mass() - particles[i].get_mass()) * NEW_V2_X_I + 2 * particles[i].get_mass() * NEW_V1_X_I / (particles[i].get_mass() + particles[j].get_mass());

                float V1_X = NEW_V1_X_F * newBasisVectorI[0] + NEW_V1_Y * newBasisVectorJ[0];
                float V1_Y = NEW_V1_X_F * newBasisVectorI[1] + NEW_V1_Y * newBasisVectorJ[1];

                float V2_X = NEW_V2_X_F * newBasisVectorI[0] + NEW_V2_Y * newBasisVectorJ[0];
                float V2_Y = NEW_V2_X_F * newBasisVectorI[1] + NEW_V2_Y * newBasisVectorJ[1];

                float dV1_X = V1_X - V1_I[0];
                float dV1_Y = V1_Y - V1_I[1];
                float dV2_X = V2_X - V2_I[0];
                float dV2_Y = V2_Y - V2_I[1];

                particles[i].update_velocity(dV1_X, dV1_Y);
                particles[j].update_velocity(dV2_X, dV2_Y);
            } 
        }
    }
    if(changed)
    {
        updatePosition();
    }
}

float BruteForce::dot_product(float* array1, float* array2)
{
    return array1[0] * array2[0] + array1[1] * array2[1] + array1[2] * array2[2];
}