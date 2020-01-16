#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <random>

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
    tournamentSelection();
}


void GeneticSelectionOperator::elitistSelection()
{
    uint32_t bestIndex;

    std::vector<ChromosomeObjectMapper> chromosomes(population->getSize());

    for (uint32_t i = 0; i < population->getSize(); ++i) {
        chromosomes[i].index = i;
        chromosomes[i].eval = 1 / evaluator->evaluate( GaUtils::chromosomeToIntArray(population->at(i)) );
    }

    sort(chromosomes.begin(), chromosomes.end(), [](const ChromosomeObjectMapper& objA, const ChromosomeObjectMapper& objB){
        return objA.eval > objB.eval;
    });

    Population newPop(configObject->populationSize);

    bestIndex = 0;

    while (bestIndex < configObject->populationSize) {
        newPop.addChromosome(population->at(bestIndex++));
    }

    population->reset(newPop);

}

void GeneticSelectionOperator::wheelOfFortuneSelection()
{
    uint32_t    sz = population->getSize();
    uint32_t    ii;
    uint32_t    jj;
    double      T;
    
    std::vector<double> eval(sz);
    std::vector<double> q(sz);
    std::vector<double> p(sz);

    for (ii = 0; ii < population->getSize(); ++ii) {
        std::vector<int> array = GaUtils::chromosomeToIntArray(population->at(ii));
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

void GeneticSelectionOperator::tournamentSelection()
{
    uint32_t bestIndex;
    int J;

    std::vector<ChromosomeObjectMapper> com(population->getSize());

    for (uint32_t i = 0; i < population->getSize(); ++i) {
        com[i].index = i;
        com[i].eval = 1 / evaluator->evaluate( GaUtils::chromosomeToIntArray(population->at(i)) );
    }

    sort(com.begin(), com.end(), [](const ChromosomeObjectMapper& objA, const ChromosomeObjectMapper& objB){
        return objA.eval > objB.eval;
    });

    Population newPop(configObject->populationSize);

    bestIndex = 0;
    while (bestIndex < configObject->populationSize) {
        
        std::vector<int> tournamentCandidatesIndices;
        std::vector<bool> viz(com.size(), 0);

        for (int i = 0; i < (int)com.size(); ++i) {
            tournamentCandidatesIndices.push_back(i);
        }

        std::mt19937 randomNumberGenerator(time(0));
        std::uniform_int_distribution<int> distribution(0, com.size());

        std::shuffle(tournamentCandidatesIndices.begin(), tournamentCandidatesIndices.end(), randomNumberGenerator);

        J = distribution(randomNumberGenerator);
        int cindex;
        for (int i = 0; i < J; ++i) {
            cindex = com[ tournamentCandidatesIndices[i] ].index;
            if (!viz[cindex]) {
                newPop.addChromosome( population->at( cindex ) );
                bestIndex++;
                
                if (bestIndex >= configObject->populationSize) {
                    break;
                }

                viz[cindex] = 1; 
            }
        }
    }

    population->reset(newPop);
}
