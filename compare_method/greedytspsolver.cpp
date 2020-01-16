#include "greedytspsolver.h"
#include <iostream>

GreedyTspSolver::GreedyTspSolver()
{

}

void GreedyTspSolver::solve(const UndirectedGraph& graph)
{
    uint32_t startNode;
    double globalMin = 1000000;
    
    for (startNode = 1; startNode <= graph.getSize(); ++startNode) {
        double sol = solveOne(graph, startNode);
        if (sol < globalMin) {
            globalMin = sol;
        }
    }

    std::cout << globalMin << '\n';
}

double GreedyTspSolver::solveOne(const UndirectedGraph& graph, uint32_t startNode)
{
    uint32_t nodeCount = 1;
    const uint32_t INF = 1000000;
    uint32_t currentNode;
    double min = INF;
    int nextNode = -1;
    std::vector<uint32_t> neighbors;
    
    std::vector<int> sol;
    std::vector<bool> viz(graph.getSize(), false);

    sol.push_back(startNode);
    currentNode = startNode;
    viz[currentNode] = 1;

    while (nodeCount < graph.getSize())
    {
        min = INF;
        nextNode = -1;
        neighbors = graph.getNeighbors(currentNode);

        for (auto it : neighbors) {
            if ( graph.getEdgeValue(it, currentNode) < min && !viz[it] ) {
                nextNode = it;
                min = graph.getEdgeValue(it, currentNode);
            }
        }

        if (nextNode == -1) {
            break;
        }

        currentNode = nextNode;
        viz[currentNode] = true;
        sol.push_back(currentNode);
    }

    if (graph.isHamiltonianCycle(sol)) {
        
        double sum = 0;

        for (int i = 0; i < sol.size() - 1; ++i) {
            sum += graph.getEdgeValue(sol[i], sol[i+1]);
        }

        return sum;
    }


    return INF;
}