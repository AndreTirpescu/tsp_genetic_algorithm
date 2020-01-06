#include <iostream>
#include <map>
#include <cstring>

#include "geneticalgorithmconfig.h"

#define UNUSED(X) (void)(X)

int main()
{
    GeneticAlgorithmConfig config;	

    config.populationSize          = 100;	
    config.maxGenerations          = 1000;	
    config.mutationProbability     = 0.01;	
    config.crossoverProbability    = 0.2;
    
    UNUSED(config);

    system("pause");
    return 0;
}