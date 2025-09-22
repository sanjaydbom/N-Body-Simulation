#include <iostream>
#include <vector>
#include "Particle.h"

class BruteForce{
public:
    BruteForce(std::vector<Particle>& p);
    void step();
    void getPositions(float* pos_arr);

private:
    std::vector<Particle> particles;
    std::vector<std::pair<float, float>> accel;
    void updateVelocity();
    void updatePosition();
    void calculateAccelerations();
    void checkCollisions();
    float dot_product(float* array1, float* array2);
};