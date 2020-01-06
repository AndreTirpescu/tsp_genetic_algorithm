#ifndef GA_FUNCTION_H
#define GA_FUNCTION_H

#include <cstdint>
#include <vector>

typedef double (*CALLBACK_GA_FUNC)(uint32_t arrayCount, double *arrayValues);

class GaFunction
{
public:
    GaFunction(double min, double max, CALLBACK_GA_FUNC func);

    GaFunction& setData(const std::vector<double> & val);

    double operator()();

    double      delta();
    double      getMaxDomain();
    double      getMinDomain();

private:
    double                  minDomain;
    double                  maxDomain;
    CALLBACK_GA_FUNC        eval;
    std::vector<double>      arrayValues;
};

#endif