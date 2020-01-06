#include <iostream>

#include "chromosome.h"
#include "population.h"
#include "minimageneticalgorithm.h"
#include "gaevalfunctions.h"
#include "geneticalgorithmconfig.h"
#include "mutationoperator.h"

#include <map>
#include <cstring>

struct FuncDataDomain
{
    double min;
    double max;
};

int main()
{
    CALLBACK_GA_FUNC fnc[] = {GaEvalFunctions::Rosenbrock, GaEvalFunctions::Griewangk, GaEvalFunctions::Rastrigin};
    std::map<CALLBACK_GA_FUNC, std::string> funcNames = 
    {
        {GaEvalFunctions::Rosenbrock,   "Rosenbrock"},
        {GaEvalFunctions::Griewangk,    "Griewangk"},
        {GaEvalFunctions::Rastrigin,    "Rastrigin"},

    };

    std::map<CALLBACK_GA_FUNC, FuncDataDomain> funcDomain = 
    {
        {GaEvalFunctions::Rosenbrock,   {-2.048, 2.048}},
        {GaEvalFunctions::Griewangk,    {-600, 600}},
        {GaEvalFunctions::Rastrigin,    {-5.12, 5.12}},
    };


    char buffer[10];
    memset(buffer, 0, 10);

    uint32_t  dimensions[] = {30};

    GeneticAlgorithmConfig config;

    config.POPULATION_SIZE          = 100;
    config.MAX_GENERATIONS          = 100000;
    config.MUTATION_PROBABILITY     = 0.01;
    config.CROSSOVER_PROBABILITY    = 0.2;
    config.PRECISION                = 10;

    for (CALLBACK_GA_FUNC cb : fnc) {
        for (uint32_t DIMENSION : dimensions) {
            for (int runs = 0; runs < 30; ++runs) {
                CustomPopulationGenerator generator;
                GaFunction gaFunc(funcDomain[cb].min, funcDomain[cb].max, cb);
                MinimaGeneticAlgorithm algorithm(gaFunc, generator, config);
                itoa(DIMENSION, buffer, 10);
                std::string fileName = funcNames[cb];
                fileName += "_";
                fileName += buffer;
                algorithm.run(DIMENSION, fileName.c_str());
            }
        }
    }

    system("pause");
    return 0;
}