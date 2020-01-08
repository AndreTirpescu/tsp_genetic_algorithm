#ifndef GA_UTILS
#define GA_UTILS

#include <vector>
#include <memory>
#include <cmath>

#include "chromosome.h"
#include "geneticalgorithmconfig.h"

class GaUtils
{
public:
    static std::vector<double> chromosomeToDoubleArray(Chromosome c, double a, double b, 
        const GeneticAlgorithmConfig& configObject)
    {
        double  delta        = abs(b - a) ;
        uint32_t N          = delta * pow(10, configObject.precision);
        uint32_t n          = ceil(log(N));

        std::vector<double> result;

        for (int i = 0; i < (int)c.getSize(); i += n) {
            int decimal = 0;
            uint32_t k = 0;
            for(int j = i + n - 1; j >= (int)i; --j) {
                decimal += c.at(j) * pow(2, k++); 
            }

            double xReal = a + decimal * delta / (pow(2, n) - 1);
            
            result.push_back(xReal);
        }

        return result;
    }

    static std::vector<int> chromosomeToIntArray(Chromosome chromosome, double a, double b)
    {
        double      delta      = abs(b - a) ;
        uint32_t    N          = delta * pow(10, 0);
        uint32_t    n          = ceil(log2(N));
        int         decimal;
        uint32_t    k;
            
        std::vector<int> result;

        for (int i = 0; i < (int)chromosome.getSize(); i += n) {
            decimal = 0;
            k = 0;

            for(int j = i + n - 1; j >= (int)i; --j) {
                decimal += chromosome.at(j) * pow(2, k++); 
            }

            double x = a + decimal * delta / (pow(2, n) - 1);

            result.push_back((int)x);
        }

        return result;
    }

};


#endif