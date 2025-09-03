#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Particle.h"
#include "BruteForce.h"



int main()
{
    srand(time(0));
    std::vector<Particle> particles = createNParticles(2);

    BruteForce bf(particles);

    for(int i = 0; i < 100; i++)
    {
        bf.step();
    }


}

std::vector<Particle> createNParticles(int N)
{
    std::vector<Particle> temp;
    for(int i = 0; i < N; i++)
    {
        Particle p(100,rand() % 100, rand() % 100, 1, 0, 0);
        temp.push_back(p);
    }
    return temp;
}