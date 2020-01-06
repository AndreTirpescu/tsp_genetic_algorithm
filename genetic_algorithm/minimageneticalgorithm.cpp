#include "minimageneticalgorithm.h"
#include "mutationoperator.h"
#include "crossoveroperator.h"
#include "selectionoperator.h"
#include "gautils.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

MinimaGeneticAlgorithm::MinimaGeneticAlgorithm(GaFunction func, CustomPopulationGenerator generator,
    GeneticAlgorithmConfig configObject)
    : function(func)
    , generator(generator)
    , configObject(configObject)
{}


void MinimaGeneticAlgorithm::run(uint32_t DIMENSION, const char* outputFile)
{
    generatePopulation(DIMENSION);
    loadOperators(DIMENSION);

    std::ofstream fout;
    fout.open(outputFile, std::ios::app);
    
    double minn;

    for (uint32_t T = 0; T < configObject.MAX_GENERATIONS; ++T) {
        (*mutation)();
        (*crossover)();
        (*selection)();

        // std::cout << "\tCurrent Best solution: " << getBestMinimum(DIMENSION) << '\n';
        minn = getBestMinimum();
        std::cout << "Generation: " << T << '\t' << "Minimum: " << minn << '\n';
    }

    fout << minn << '\n';
}

void MinimaGeneticAlgorithm::generatePopulation(uint32_t DIMENSION)
{
    pop = generator.generatePopulation(
        configObject.POPULATION_SIZE, 
        function.delta(), 
        configObject.PRECISION,
        DIMENSION
    );
}

void MinimaGeneticAlgorithm::loadOperators(uint32_t DIMENSION)
{
    mutation    = new GeneticMutationOperator(&pop, &configObject);
    crossover   = new GeneticCrossoverOperator(&pop, &configObject);
    selection   = new GeneticSelectionOperator(&pop, &configObject, function, DIMENSION);
}

double MinimaGeneticAlgorithm::getBestMinimum()
{
    double MIN = 10000000;

    for (uint32_t i = 0; i < pop.getSize(); ++i) {
        std::vector<double> array = GaUtils::chromosomeToArray(
            pop.at(i), 
            function.getMinDomain(),
            function.getMaxDomain(),
            configObject
        );

        function.setData(array);
        MIN = std::min(MIN, function());
    }

    return MIN;
}

