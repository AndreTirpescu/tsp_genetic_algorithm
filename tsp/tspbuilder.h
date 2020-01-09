#ifndef TSPBUILDER_H
#define TSPBUILDER_H

#include "tspformatreader.h"
#include "undirectedgraph.h"

class TspBuilder
{
public:
    TspBuilder(TspFormatReader* formatReader);

    UndirectedGraph buildTspProblem();
    void            linkGraph(UndirectedGraph* graph);
    void            loadEdgeValues(const std::vector< std::pair<float, float> >& values, UndirectedGraph *graph);

private:
    TspFormatReader* formatReader;

};

#endif