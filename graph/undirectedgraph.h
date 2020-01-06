#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <cstdint>

class UndirectedGraph
{
public:
    UndirectedGraph(uint32_t size);

    uint32_t getSize() const;
 
    void linkNodes(uint32_t indexA, uint32_t indexB);

private:
    uint32_t                        size;    
    std::vector< std::vector<uint32_t> >  adiacenyList;
};

#endif