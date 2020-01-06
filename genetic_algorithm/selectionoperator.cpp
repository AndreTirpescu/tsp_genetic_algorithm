#include <cstdlib>
#include <iostream>
#include <cmath>

#include "selectionoperator.h"
#include "gautils.h"

GeneticSelectionOperator::GeneticSelectionOperator(Population *pop, GeneticAlgorithmConfig *cfg,
    const GaFunction& func, uint32_t dim) 
    : population(pop)
    , configObject(cfg)
    , function(func)
    , dimensions(dim)
{}

void GeneticSelectionOperator::operator()()
{
    uint32_t sz = population->getSize();
    std::vector<double> eval(sz);
    std::vector<double> q(sz);
    std::vector<double> p(sz);

    double T        = 0;

    for (uint32_t i = 0; i < population->getSize(); ++i) {
        std::vector<double> array = GaUtils::chromosomeToArray(
            population->at(i), 
            function.getMinDomain(),
            function.getMaxDomain(),
            *configObject
        );

        function.setData(array);
        
        eval[i] = 1 / function();
        T += eval[i];
    }

    for (uint32_t i = 0; i < population->getSize(); ++i) {
        p[i] = eval[i] / T;
    }

    q[0] = 0;
    for (uint32_t i = 0; i < population->getSize() - 1; ++i) {
        q[i+1] = q[i] + p[i];
    }

    Population newPop(configObject->POPULATION_SIZE);

    for (uint32_t i = 0; i < newPop.getSize(); ) {
        double randomNumber = ((double) rand() / (RAND_MAX)); 
        for (uint32_t j = 0; j < population->getSize() - 1; ++j) {
            if (q[j] < randomNumber && randomNumber < q[j+1]) {
                newPop.addChromosome(population->at(j));
                ++i;
            }
        }
    }

    population->reset(newPop);
}

