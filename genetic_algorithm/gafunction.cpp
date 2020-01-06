#include "gafunction.h"
#include <cstring>
#include <cmath>

#ifdef GENETIC_DEBUG
    #include <iostream>
#endif

GaFunction::GaFunction(double min, double max, CALLBACK_GA_FUNC func) 
    : minDomain(min)
    , maxDomain(max)
    , eval(func)
{}

double GaFunction::operator()()
{
    return eval(arrayValues.size(), arrayValues.data());
}

GaFunction& GaFunction::setData(const std::vector<double> & val)
{
    arrayValues.clear();
    
    for (auto it : val) {
        arrayValues.push_back(it);
    }

    return *this;
}

double GaFunction::delta()
{
    return abs(maxDomain - minDomain);
}

double GaFunction::getMaxDomain()
{
    return maxDomain;
}

double GaFunction::getMinDomain()
{
    return minDomain;
}