#ifndef TSP_EVALUATOR_H
#define TSP_EVALUATOR_H

#include "undirectedgraph.h"

#include <vector>


class TspEvaluator
{

public:
    TspEvaluator(UndirectedGraph *graph);

    double evaluate(std::vector<int> nodes);

private:
    UndirectedGraph *graph;
    
    const double          INVALID_VALUE{1000000000};
};

#endif