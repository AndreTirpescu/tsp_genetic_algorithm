#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>

#include "selectionoperator.h"
#include "gautils.h"

GeneticSelectionOperator::GeneticSelectionOperator(Population *pop, GeneticAlgorithmConfig *cfg, TspEvaluator * evaluator, UndirectedGraph *graph) 
    : population(pop)
    , configObject(cfg)
    , evaluator(evaluator)
    , graph(graph)
{}

void GeneticSelectionOperator::operator()()
{
    uint32_t    sz = population->getSize();
    uint32_t    ii;
    uint32_t    jj;
    double      T;
    
    std::vector<double> eval(sz);
    std::vector<double> q(sz);
    std::vector<double> p(sz);

    for (ii = 0; ii < population->getSize(); ++ii) {
        std::vector<int> array = GaUtils::chromosomeToIntArray(population->at(ii), 1, graph->getSize());
        eval[ii] = 1 / evaluator->evaluate(array);

        T += eval[ii];
    }

    for (ii = 0; ii < population->getSize(); ++ii) {
        p[ii] = eval[ii] / T;
    }

    q[0] = 0;
    for (ii = 0; ii < population->getSize() - 1; ++ii) {
        q[ii+1] = q[ii] + p[ii];
    }

    Population newPop(configObject->populationSize);

    for (ii = 0; ii < newPop.getSize();) {
        srand(time(0));
        double randomNumber = ((double) rand() / (RAND_MAX)); 
        
        for (jj = 0; jj < population->getSize() - 1; ++jj) {
        
            if (q[jj] < randomNumber && randomNumber < q[jj + 1]) {
        
                newPop.addChromosome(population->at(jj));
        
                ++ii;
            }
        }
    }

    population->reset(newPop);
}
