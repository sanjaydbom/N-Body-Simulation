#include <iostream>
#include <random>
#include <chrono>
#include "Particle.h"
#include "BruteForce.h"
#include "Visualizer.h"



std::vector<Particle> createNParticles(int N)
{
    std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    float min_val = 0.0f;
    float max_val = 1.0f;
    std::uniform_real_distribution<float> distr(min_val, max_val);
    std::vector<Particle> temp;
    for(int i = 0; i < N; i++)
    {
        Particle p(1,distr(eng), distr(eng), 1, 0, 0);
        temp.push_back(p);
    }
    return temp;
}

int main()
{
    const int N = 2;
    std::vector<Particle> particles = createNParticles(N);
    float radii[N];
    for(int i = 0; i < N; i++)
    {
        radii[i] = 0.05f;
    }

    BruteForce bf(particles);

    float bgColor[] = {0.0,0.0,0.0,1.0};
    float oColor[] = {1.0,1.0,1.0,1.0};
    Visualizer GUI(800,600,bgColor, oColor, 50, 2);
    float pos_arr[3 * N];
    bf.getPositions(pos_arr);

    std::cout << pos_arr[0] << " " << pos_arr[1] << "\n" << pos_arr[3] << " " << pos_arr[4] << "\n";

    std::cout << "Starting rendering\n";
    int i = 0;
    while(GUI.render(pos_arr, radii)){
            bf.step();
            bf.getPositions(pos_arr);
    }
    std::cout << "Rendering done\n";
    return 0;


}