/*#include <iostream>
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
}*/
#include "Visualizer.h"

int main(){
    float bgColor[] = {0.0,0.0,0.0,1.0};
    float oColor[] = {1.0,1.0,1.0,1.0};
    Visualizer GUI(800,600,bgColor, oColor, 50, 2);

    const float center[] = {
        0.0f, 0.0f, 0.0f, //center 1
        0.35f, 0.0f, 0.0f //center 2
    };
    const float radii[] = {
        0.25f,
        0.10f
    };


    std::cout << "Starting rendering\n";
    while(GUI.render(center, radii));
    std::cout << "Rendering done\n";
    return 0;
}