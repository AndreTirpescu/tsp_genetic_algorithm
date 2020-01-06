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

    static std::vector<int> chromosomeToIntArray(Chromosome chromosome)
    {
        const uint32_t      BIT_LENGTH = 32;
        std::vector <int>   result;

        int  chrIndex;
        int  numberIndex;
        int  numberIndexStart;
        int  number;
        int  powCnt;

        for (chrIndex = 0; chrIndex < (int)chromosome.getSize(); chrIndex += BIT_LENGTH) {
            
            numberIndexStart = chrIndex + BIT_LENGTH - 1;
            
            number = 0;
            powCnt = 0;

            for (numberIndex = numberIndexStart; numberIndex >= (int)chrIndex; --numberIndex) {
                number += pow(2, powCnt++) * chromosome.at(numberIndex); 
            }

            result.push_back(number);
        }
        
        return result;
    }

};


#endif