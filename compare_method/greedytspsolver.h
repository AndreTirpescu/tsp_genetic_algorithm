#ifndef GREEDY_TSP_SOLVER_H
#define GREEDY_TSP_SOLVER_H

#include "undirectedgraph.h"

class GreedyTspSolver
{
public:
    GreedyTspSolver();

    void solve(const UndirectedGraph& graph);
    
    double solveOne(const UndirectedGraph& graph, uint32_t startNode);
};

#endif