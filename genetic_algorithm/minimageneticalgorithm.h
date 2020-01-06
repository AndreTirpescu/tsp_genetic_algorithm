#ifndef MINIMA_GENETIC_ALGORITHM_H
#define MINIMA_GENETIC_ALGORITHM_H

#include "populationgenerator.h"
#include "geneticalgorithmconfig.h"
#include "gafunction.h"
#include "igeneticoperator.h"

class MinimaGeneticAlgorithm
{
public:
    MinimaGeneticAlgorithm(GaFunction func, CustomPopulationGenerator generator, 
        GeneticAlgorithmConfig configObject);

    void run(uint32_t DIMENSION, const char* outputFile);

private:
    Population                  pop;
    GaFunction                  function;
    CustomPopulationGenerator   generator;
    GeneticAlgorithmConfig      configObject;
    IGeneticOperator            *mutation;
    IGeneticOperator            *crossover;
    IGeneticOperator            *selection;

    void                        generatePopulation(uint32_t DIMENSION);
    void                        loadOperators(uint32_t DIMENSION);
    double                      getBestMinimum();
};

#endif