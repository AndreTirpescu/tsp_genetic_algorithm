#ifndef MINIMA_GENETIC_ALGORITHM_H
#define MINIMA_GENETIC_ALGORITHM_H

#include "populationgenerator.h"
#include "geneticalgorithmconfig.h"
#include "gafunction.h"
#include "igeneticoperator.h"
#include "undirectedgraph.h"
#include "tspevaluator.h"

class TspGeneticAlgorithm
{
public:
    TspGeneticAlgorithm(CustomPopulationGenerator generator, GeneticAlgorithmConfig configObject, UndirectedGraph *graph);

    void run(const char* outputFile);

private:
    CustomPopulationGenerator   generator;
    GeneticAlgorithmConfig      configObject;
    UndirectedGraph             *graph;
    Population                  pop;
    IGeneticOperator            *mutation;
    IGeneticOperator            *crossover;
    IGeneticOperator            *selection;
    TspEvaluator                evaluator;


    void                        loadOperators();
    double                      getBestMinimum();
};

#endif