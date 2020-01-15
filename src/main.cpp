#include <iostream>
#include <map>
#include <cstring>

#include "geneticalgorithmconfig.h"
#include "undirectedgraph.h"
#include "tspgeneticalgorithm.h"
#include "tspformatreader.h"
#include "tspbuilder.h"

#define UNUSED(X) (void)(X)

int main()
{
    GeneticAlgorithmConfig config;	
    CustomPopulationGenerator generator;

    config.populationSize          = 100;	
    config.maxGenerations          = 100000;	
    config.mutationProbability     = 0.8;	
    config.crossoverProbability    = 0.2;
    config.precision               = 0;
    

    TspFormatReader reader("data.in");
    TspBuilder tspBuilder(&reader);

    UndirectedGraph graph = tspBuilder.buildTspProblem();

    TspGeneticAlgorithm geneticAlg(generator, config, &graph);

    geneticAlg.run("date.out");

    system("pause");
    return 0;
}