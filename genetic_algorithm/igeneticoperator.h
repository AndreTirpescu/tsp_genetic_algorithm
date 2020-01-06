#ifndef GENETIC_OPERATOR_INTERFACE
#define GENETIC_OPERATOR_INTERFACE

class IGeneticOperator
{
public:
    virtual void operator()() = 0;
};


#endif