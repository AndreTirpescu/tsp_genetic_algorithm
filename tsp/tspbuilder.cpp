#include "tspbuilder.h"

#include <cmath>

TspBuilder::TspBuilder(TspFormatReader* formatReader) : formatReader(formatReader)
{}

UndirectedGraph TspBuilder::buildTspProblem()
{
    formatReader->readHeaderInfo(5);
    std::vector< std::pair<float, float> > data = formatReader->readData();

    uint32_t graphSize = atoi( formatReader->getHeaderDataFor(HEADER_INFO_DATA_DIMENSION).c_str() );

    UndirectedGraph graph(graphSize);

    linkGraph(&graph);

    loadEdgeValues(data, &graph);

    return graph;
}

void TspBuilder::linkGraph(UndirectedGraph *graph)
{
    uint32_t indexA, indexB;

    //@TODO can be heavily improved upon
    for(indexA = 1; indexA <= graph->getSize(); ++indexA) {
        for (indexB = 1; indexB <= graph->getSize(); ++indexB) {
                if (indexA != indexB) {
                    graph->linkNodes(indexA, indexB);
                }
        }
    }
}


void TspBuilder::loadEdgeValues(const std::vector< std::pair<float, float> > &values, UndirectedGraph *graph)
{
    uint32_t indexA, indexB;

    //@TODO can be heavily improved upon
    for(indexA = 1; indexA <= graph->getSize(); ++indexA) {
        for (indexB = 1; indexB <= graph->getSize(); ++indexB) {
                double dist = sqrt( pow(values[indexA].first - values[indexB].first, 2) + pow(values[indexA].second - values[indexB].second, 2)  );
                graph->setEdgeValue(indexA, indexB, dist);
        }
    }
}
