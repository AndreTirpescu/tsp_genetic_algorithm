#ifndef CROSSOVER_OPERATOR_H
#define CROSSOVER_OPERATOR_H

#include "igeneticoperator.h"

#include "population.h"
#include "geneticalgorithmconfig.h"

struct CrossOverObject
{
    int     index;
    double  probability;
};


class GeneticCrossoverOperator : public IGeneticOperator
{
public:
    GeneticCrossoverOperator(Population *pop, GeneticAlgorithmConfig *cfg);

    void operator()() override;

private:
    Population                  *population;
    GeneticAlgorithmConfig      *configObject;
    CrossOverObject             *crossoverData;

    void                        fillCrossover();
    void                        sortCrossoverData();
    void                        crossoverChromosomes(uint32_t c1, uint32_t c2);
};

#endif