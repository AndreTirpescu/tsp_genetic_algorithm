#ifndef SELECTION_OPERATOR_H
#define SELECTION_OPERATOR_H

#include "igeneticoperator.h"
#include "population.h"
#include "geneticalgorithmconfig.h"
#include "gafunction.h"


class GeneticSelectionOperator : public IGeneticOperator 
{
public:
    GeneticSelectionOperator(Population *pop, GeneticAlgorithmConfig *cfg, const GaFunction& func, 
        uint32_t dim);

    void operator()() override;

    // shouldn't be here but time
    double*  chromosomeToArray(Chromosome c);
private:
    Population                  *population;
    GeneticAlgorithmConfig      *configObject;
    GaFunction                  function;
    uint32_t                    dimensions;
};

#endif