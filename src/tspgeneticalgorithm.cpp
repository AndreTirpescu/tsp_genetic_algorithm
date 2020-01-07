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
    double minn;
    uint32_t T;

    configObject.dimension = graph->getSize();

    pop = generator.generatePopulation(configObject);

    loadOperators();

    std::ofstream fout;
    fout.open(outputFile, std::ios::app);
    
    for (T = 0; T < configObject.maxGenerations; ++T) {
        (*mutation)();
        (*crossover)();
        (*selection)();

        minn = getBestMinimum();
        std::cout << "Generation: " << T << '\t' << "Minimum: " << minn << '\n';
    }

    fout << minn << '\n';
}

void TspGeneticAlgorithm::loadOperators()
{
    mutation    = new GeneticMutationOperator(&pop, &configObject);
    crossover   = new GeneticCrossoverOperator(&pop, &configObject);
    selection   = new GeneticSelectionOperator(&pop, &configObject, &evaluator);
}

double TspGeneticAlgorithm::getBestMinimum()
{
    double minimum = INF;

    for (uint32_t i = 0; i < pop.getSize(); ++i) {
        std::vector<int> array = GaUtils::chromosomeToIntArray(pop.at(i));

    }

    return minimum;
}