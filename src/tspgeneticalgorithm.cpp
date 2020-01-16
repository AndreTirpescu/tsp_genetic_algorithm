#include "tspgeneticalgorithm.h"
#include "mutationoperator.h"
#include "crossoveroperator.h"
#include "selectionoperator.h"
#include "gautils.h"

#define INF 1000000000

#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

TspGeneticAlgorithm::TspGeneticAlgorithm(CustomPopulationGenerator generator, GeneticAlgorithmConfig configObject, UndirectedGraph *graph)
    : generator(generator)
    , configObject(configObject)
    , graph(graph)
    , mutation(nullptr)
    , crossover(nullptr)
    , selection(nullptr)
    , evaluator(graph)
{}

void TspGeneticAlgorithm::run(const char* outputFile)
{
    uint32_t    T;

    configObject.dimension = graph->getSize();

    pop = generator.generatePopulation(configObject);

    loadOperators();

    std::ofstream fout;
    fout.open(outputFile, std::ios::app);

    globalMinimum = INF;

    uint32_t breakWhenNoChange;
    
    for (T = 0; T < configObject.maxGenerations; ++T) {
        (*mutation)();
        (*crossover)();
        (*selection)();

        std::pair<double, std::vector<int> > minData = getBestMinimum();
        
        if (minData.first < globalMinimum) {
            globalMinimum =  minData.first;
            bestSol = minData.second;
            breakWhenNoChange = 0;
        }
        else {
            breakWhenNoChange++;
            if (breakWhenNoChange > 10000) {
                break;
            }
        }


        std::cout << "Generation: " << T << '\t' << "Minimum: " << globalMinimum << '\t';

        double sum = 0;
        for (int it = 0; it < (int)bestSol.size() - 1; ++it) {
            sum += graph->getEdgeValue(bestSol[it], bestSol[it + 1]);
        }

        std::cout << "Best SOL val: " << sum;

        std::cout << '\n';
    }

    fout << globalMinimum << '\n';
}

void TspGeneticAlgorithm::loadOperators()
{
    mutation    = new GeneticMutationOperator(&pop, &configObject);
    crossover   = new GeneticCrossoverOperator(&pop, &configObject);
    selection   = new GeneticSelectionOperator(&pop, &configObject, &evaluator, graph);
}

std::pair<double, std::vector<int> > TspGeneticAlgorithm::getBestMinimum()
{
    double minimum = INF;
    std::vector<int> minArray;

    for (uint32_t i = 0; i < pop.getSize(); ++i) {
        std::vector<int> array = GaUtils::chromosomeToIntArray(pop.at(i));
        double eval = evaluator.evaluate(array);

        if (eval < minimum) {
            minimum = eval;
            minArray = array;
        }
    }

    return {minimum, minArray};
}