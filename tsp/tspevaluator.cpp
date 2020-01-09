#include "tspevaluator.h"

#include <set>

TspEvaluator::TspEvaluator(UndirectedGraph *graph) : graph(graph)
{}

double TspEvaluator::evaluate(std::vector<int> nodes)
{
    double solBias;
    double diffBias;
    double sum;
    uint32_t index;

    std::set<int> uniqeNodes;

    for (auto it : nodes) {
        uniqeNodes.insert(it);
    }

    diffBias = 1.0 / uniqeNodes.size();

    if (uniqeNodes.size() > 50) {
        solBias = 0.0001;
    }

    if (graph->isHamiltonianCycle(nodes)) {
        solBias = 0.000001;
    }
    else {
        solBias = 1.0;
    }

    sum = 0;
    for (index = 0; index < nodes.size() - 1; ++index) {
        sum += graph->getEdgeValue(nodes[index], nodes[index+1]);
    }

    if (sum == 0) {
        return INVALID_VALUE;
    }

    return sum * solBias * diffBias;
}
