#include <iostream>
#include <map>
#include <cstring>

#include "geneticalgorithmconfig.h"
#include "undirectedgraph.h"
#include "tspgeneticalgorithm.h"
#include "tspformatreader.h"
#include "tspbuilder.h"
#include "greedytspsolver.h"

#define UNUSED(X) (void)(X)

int main()
{
    GeneticAlgorithmConfig config;	
    CustomPopulationGenerator generator;

    config.populationSize          = 100;	
    config.maxGenerations          = 40000;
    config.mutationProbability     = 0.02;
    config.crossoverProbability    = 0.3;
    config.precision               = 0;
    
    std::vector<std::string> tspFiles{"berlin52", "kroe100", "a280"};

    for (auto it : tspFiles)
    {
        for (int i = 0; i < 15; ++i) {
            TspFormatReader reader((it + ".in").c_str());
            TspBuilder tspBuilder(&reader);

            UndirectedGraph graph = tspBuilder.buildTspProblem();

            TspGeneticAlgorithm geneticAlg(generator, config, &graph);

            geneticAlg.run((it + ".out").c_str());
        }
    }


    // for (auto it : tspFiles) {
    //     TspFormatReader reader((it + ".in").c_str());
    //     TspBuilder tspBuilder(&reader);

    //     UndirectedGraph graph = tspBuilder.buildTspProblem();

    //     GreedyTspSolver x;
        
    //     x.solve(graph);

    // }
    

    system("pause");
    return 0;
}