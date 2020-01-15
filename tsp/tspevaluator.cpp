#include "tspevaluator.h"

#include <set>

TspEvaluator::TspEvaluator(UndirectedGraph *graph) : graph(graph)
{}

double TspEvaluator::evaluate(std::vector<int> nodes)
{
    double sum;
    uint32_t index;

    // if (graph->isHamiltonianCycle(nodes)) {
    //     solBias = 0.000001;
    // }
    // else {
    //     solBias = 1.0;
    // }

    sum = 0;
    for (index = 0; index < nodes.size() - 1; ++index) {
        sum += graph->getEdgeValue(nodes[index], nodes[index+1]);
    }

    return sum;
}
