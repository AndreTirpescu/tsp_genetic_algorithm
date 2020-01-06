#include "tspevaluator.h"

TspEvaluator::TspEvaluator(UndirectedGraph *graph) : graph(graph)
{}

double TspEvaluator::evaluate(std::vector<int> nodes)
{
    if (!graph->isPath(nodes)) {
        return INVALID_VALUE;
    }

    double sum;
    uint32_t index;

    for (index = 0; index < nodes.size() - 1; ++index) {
        sum += graph->getEdgeValue(nodes[index], nodes[index+1]);
    }

    return sum;
}
