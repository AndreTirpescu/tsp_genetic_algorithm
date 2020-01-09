#ifndef GA_UTILS
#define GA_UTILS

#include <vector>
#include <memory>
#include <queue>
#include <cmath>

#include <set>
#include <iostream>
#include <bitset>

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
        double      delta      = abs(b - a);
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

    static void normalize(Chromosome& c, double a, double b, const GeneticAlgorithmConfig& config)
    {
        std::vector<int> nodes = chromosomeToIntArray(c, a, b);
        std::vector<int> viz(1000, 0);
        std::queue<int>  unused;
        std::vector<int> newNodes;

        uint32_t size = nodes.size();
        uint32_t nodeIndex = 0;

        for (auto it : nodes) {
            viz[it]++;
        }

        for (auto it : nodes) {
            if (viz[it] >= 1) {
                viz[it] = -1;
                newNodes.push_back(it);
            }
        }

        for (nodeIndex = 1; nodeIndex <= size; ++nodeIndex) {
            if (viz[nodeIndex] == 0) {
                unused.push(nodeIndex);
            }
        }

        while(!unused.empty()) 
        {
            int indexUnused = unused.front();
            newNodes.push_back(indexUnused);
            unused.pop();
        }

        uint32_t N          = (config.dimension - 1) * pow(10, config.precision);
        uint32_t bitLength  = ceil(log2(N));

        int k = 0, index;
        int cpy;
        for(auto it : newNodes){
            std::bitset<32> bset(it);
            for(index = 0; index <= bitLength; ++index) {
                c.set(k++, bset[index]);
            }
        }

        std::vector<int> check = chromosomeToIntArray(c, a, b);

        return;
    }

};


#endif