#include <iostream>
#include <random>
#include <chrono>

#include "Particle.h"
#include "BruteForce.h"
#include "Visualizer.h"
#include "Constants.h"



std::vector<Particle> createNParticles(const int N)
{
    std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> distr(-1.0, 1.0);
    std::vector<Particle> temp;
    for(int i = 0; i < N; i++)
    {
        Particle p(MASS, X_LENGTH / 2 * distr(eng), Y_LENGTH / 2 * distr(eng), RADIUS, 0, 0);
        temp.push_back(p);
    }
    return temp;
}

int main()
{
    std::vector<Particle> particles = createNParticles(NUM_PARTICLES);
    BruteForce bf(particles);

    float radii[NUM_PARTICLES];
    for(int i = 0; i < NUM_PARTICLES; i++)
        radii[i] = PIXEL_RADIUS;

    Visualizer GUI(WIDTH,HEIGHT,BACKGROUND_COLOR, OBJECT_COLOR, RESOLUTION, NUM_PARTICLES, TITLE);

    float pos_arr[3 * NUM_PARTICLES];
    bf.getPositions(pos_arr);

    //for(int i = 0; i < NUM_PARTICLES; i++)
    //    std::cout << pos_arr[3 * i] << " " << pos_arr[3 * i + 1] << "\n";


    std::cout << "Starting rendering\n";
    while(GUI.render(pos_arr, radii)){
            bf.step();
            bf.getPositions(pos_arr);
    }
    std::cout << "Rendering done\n";
    return 0;


}