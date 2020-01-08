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

    configObject.dimension = graph->getSize() + 1;

    pop = generator.generatePopulation(configObject);

    loadOperators();

    std::ofstream fout;
    fout.open(outputFile, std::ios::app);

    globalMinimum = INF;
    
    for (T = 0; T < configObject.maxGenerations; ++T) {
        (*mutation)();
        (*crossover)();
        (*selection)();

        std::pair<double, std::vector<int> > minData = getBestMinimum();
        
        if (minData.first < globalMinimum) {
            globalMinimum =  minData.first;
            bestSol = minData.second;
        }

        std::cout << "Generation: " << T << '\t' << "Minimum: " << globalMinimum << '\t';

        for (auto it : bestSol) {
            std::cout << it << ' '; 
        }

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
        std::vector<int> array = GaUtils::chromosomeToIntArray(pop.at(i), 1, graph->getSize() + 1);
        double eval = evaluator.evaluate(array);

        if (eval < minimum) {
            minimum = eval;
            minArray = array;
        }
    }

    return {minimum, minArray};
}