#include <iostream>
#include <map>
#include <cstring>

#include "geneticalgorithmconfig.h"
#include "undirectedgraph.h"
#include "tspgeneticalgorithm.h"

#define UNUSED(X) (void)(X)

int main()
{
    GeneticAlgorithmConfig config;	
    CustomPopulationGenerator generator;

    config.populationSize          = 100;	
    config.maxGenerations          = 100000;	
    config.mutationProbability     = 0.2;	
    config.crossoverProbability    = 0.4;
    config.precision               = 0;
    
    UndirectedGraph graph(5);
    graph.linkNodes(1, 2).setEdgeValue(1, 2, 20);
    graph.linkNodes(1, 5).setEdgeValue(1, 5, 60);
    graph.linkNodes(1, 4).setEdgeValue(1, 4, 30);
    graph.linkNodes(2, 4).setEdgeValue(2, 4, 30);
    graph.linkNodes(4, 3).setEdgeValue(4, 3, 70);
    graph.linkNodes(2, 3).setEdgeValue(2, 3, 40);
    graph.linkNodes(4, 5).setEdgeValue(4, 5, 30);
    graph.linkNodes(5, 3).setEdgeValue(5, 3, 30);

    TspGeneticAlgorithm geneticAlg(generator, config, &graph);

    geneticAlg.run("date.out");

    system("pause");
    return 0;
}