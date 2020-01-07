#ifndef GRAPH_H
#define GRAPH_H

/*
*
*   THIS IS A GRAPH IMPLEMENTATION FOR THE GIVEN PROBLEM
*   THIS IS NOT A GENERIC IMPLEMENTATION, IT WILL CONTAIN FUNCTIONALITIES FOR THE GIVEN PROBLEM
*  
*/

#include <vector>
#include <map>
#include <cstdint>
#include <functional>


class UndirectedGraph
{
public:
    UndirectedGraph(uint32_t size);

    uint32_t getSize() const;
 
    UndirectedGraph& linkNodes(uint32_t indexA, uint32_t indexB);

    UndirectedGraph& setEdgeValue(uint32_t indexA, uint32_t indexB, double value);
    
    void parseDFS(uint32_t startNodeIndex, std::function<void(uint32_t)> callback);

    void parseBFS(uint32_t startNodeIndex, std::function<void(uint32_t)> callback);

    std::vector<uint32_t> getDfsOrder(uint32_t startNodeIndex);

    std::vector<uint32_t> getBfsOrder(uint32_t startNodeIndex);

    bool areNodeAdjacent(uint32_t indexA, uint32_t indexB);

    bool isPath(std::vector<int> nodeList);

    bool allNodesExist(std::vector<int> nodeList);

    double getEdgeValue(uint32_t indexA, uint32_t indexB);

private:
    uint32_t                                                size;    
    std::vector< std::vector<uint32_t> >                    adjacenyList;
    std::map< std::pair<uint32_t, uint32_t>, double >       edgesValues;
};

#endif