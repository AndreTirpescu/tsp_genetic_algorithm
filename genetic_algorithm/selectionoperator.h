#ifndef SELECTION_OPERATOR_H
#define SELECTION_OPERATOR_H

#include "igeneticoperator.h"
#include "population.h"
#include "geneticalgorithmconfig.h"
#include "gafunction.h"
#include "tspevaluator.h"

#include <functional>



class GeneticSelectionOperator : public IGeneticOperator 
{
public:
    GeneticSelectionOperator(Population *pop, GeneticAlgorithmConfig *cfg, TspEvaluator * evaluator, UndirectedGraph *graph);

    void operator()() override;

private:
    Population                  *population;
    GeneticAlgorithmConfig      *configObject;
    TspEvaluator                *evaluator;
    UndirectedGraph             *graph;
};

#endif