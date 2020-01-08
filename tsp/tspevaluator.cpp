#include "tspevaluator.h"

TspEvaluator::TspEvaluator(UndirectedGraph *graph) : graph(graph)
{}

double TspEvaluator::evaluate(std::vector<int> nodes)
{
    double solBias;
    double pathBias;
    double diffBias;
    double sum;
    uint32_t index, j;

    if (graph->isPath(nodes)) {
        pathBias = 0.0001;
    }
    else {
        pathBias = 1000.0;
    }

    if (graph->isHamiltonianCycle(nodes)) {
        solBias = 0.0001;
    }
    else {
        solBias = 1000.0;
    }

    bool found = false;
    for(index = 0; index < nodes.size() - 1; ++index) {
        for (j = index + 1; j < nodes.size(); ++j) {
            if (nodes[index] == nodes[j]) {
                found = true;
            }
        }
    }

    if (!found) {
        diffBias = 0.0001;
    } else {
        diffBias = 1000;
    }

    sum = 0;
    for (index = 0; index < nodes.size() - 1; ++index) {
        sum += graph->getEdgeValue(nodes[index], nodes[index+1]);
    }

    if (sum == 0) {
        return INVALID_VALUE;
    }

    return sum * solBias * pathBias * diffBias;
}
