#include <iostream>
#include "Particle.h"

class BruteForce{
public:
    BruteForce(std::vector<Particle>& p);
    void step();

private:
    std::vector<Particle> particles;
    std::vector<std::pair<float, float>> accel;
    float G = 1.0;
    void updateVelocity();
    void updatePosition();
    void calculateAccelerations();
};