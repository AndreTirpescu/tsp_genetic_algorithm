#ifndef MUTATION_OPERATOR_H
#define MUTATION_OPERATOR_H

#include "igeneticoperator.h"
#include "population.h"
#include "geneticalgorithmconfig.h"

class GeneticMutationOperator : public IGeneticOperator 
{
public:
    GeneticMutationOperator(Population *pop, GeneticAlgorithmConfig *cfg);

    void operator()() override;

private:
    Population                  *population;
    GeneticAlgorithmConfig      *configObject;
};

#endif