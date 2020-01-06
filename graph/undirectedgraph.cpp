#include "undirectedgraph.h"

UndirectedGraph::UndirectedGraph(uint32_t size) : size(size)
{

}

uint32_t UndirectedGraph::getSize() const
{
    return size;
}

void UndirectedGraph::linkNodes(uint32_t indexA, uint32_t indexB)
{
    adiacenyList[indexA].push_back(indexB);
    adiacenyList[indexB].push_back(indexA);
}