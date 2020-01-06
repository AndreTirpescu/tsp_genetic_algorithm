#ifndef GA_KNOWN_FUNCTIONS_H
#define GA_KNOWN_FUNCTIONS_H

#define _USE_MATH_DEFINES

#include <cstdint>
#include <cmath>

#ifdef GENETIC_DEBUG
    #include <iostream>
#endif

class GaEvalFunctions
{
public:
    static double Rosenbrock(uint32_t size, double* values)
    {
        double sum = 0;
        for (uint32_t i = 0; i < size - 1; ++i) {
            sum += 100 * pow((values[i+1] - pow(values[i], 2)), 2) + pow(1 - values[i], 2);
        }

        return sum;
    }

    static double Rastrigin(uint32_t size, double* values)
    {
        double sum = 0;
        for (uint32_t i = 0; i < size; ++i) {
            sum += pow(values[i], 2) - 10 * cos(2 * M_PI * values[i]);
        }

        return 10 * size + sum;
    }

    static double Griewangk(uint32_t size, double* values)
    {
        double sum = 0;

        for (uint32_t i = 0; i < size; ++i) {
            sum += pow(values[i], 2) / 4000;
        }

        double prod = 1;
        for (uint32_t i = 0; i < size; ++i) {
            prod *= cos(values[i] / sqrt(i + 1)); 
        }

        return sum - prod + 1;
    }
};

#endif