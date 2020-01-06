#include "undirectedgraph.h"

#include <queue>
#include <stack>
#include <iostream>

UndirectedGraph::UndirectedGraph(uint32_t size) 
    : size(size)
    , adjacenyList(size)
    , edgesValues()
{
}

uint32_t UndirectedGraph::getSize() const
{
    return size;
}

void UndirectedGraph::linkNodes(uint32_t indexA, uint32_t indexB)
{
    adjacenyList[indexA].push_back(indexB);
    adjacenyList[indexB].push_back(indexA);
}

void UndirectedGraph::setEdgeValue(uint32_t indexA, uint32_t indexB, double value)
{
    edgesValues[ {indexA, indexB} ] = value;
    edgesValues[ {indexB, indexA} ] = value;
}

void UndirectedGraph::parseDFS(uint32_t startNodeIndex, std::function<void(uint32_t)> onVisit)
{
    std::vector<bool>       visited(size, false);
    std::stack<uint32_t>    visitStack;

    visited[startNodeIndex] = true;
    visitStack.push(startNodeIndex);
    
    onVisit(startNodeIndex);

    while (!visitStack.empty()) {
        bool found = false;

        for (uint32_t node : adjacenyList[visitStack.top()]) {
            if (!visited[node]) {
                visitStack.push(node);
                visited[node] = true;

                onVisit(node);

                found = true;
                break;
            }
        }

        if (!found) {
            visitStack.pop();
        }
    }
}

void UndirectedGraph::parseBFS(uint32_t startNodeIndex, std::function<void(uint32_t)> onVisit)
{
    std::vector<bool>       visited(size, false);
    std::queue<uint32_t> nodeQueue;

    nodeQueue.push(startNodeIndex);
    visited[startNodeIndex] = true;
    onVisit(startNodeIndex);

    while (!nodeQueue.empty()) {
        for (uint32_t node : adjacenyList[nodeQueue.front()]) {
            if (!visited[node]) {
                nodeQueue.push(node);
                visited[node] = true;
                onVisit(node);
            }
        }

        nodeQueue.pop();
    }
}

std::vector<uint32_t> UndirectedGraph::getDfsOrder(uint32_t startNodeIndex)
{
    std::vector<uint32_t>   result;
    parseDFS(startNodeIndex, [&](uint32_t index) {
        result.push_back(index);
    });

    return result;
}

std::vector<uint32_t> UndirectedGraph::getBfsOrder(uint32_t startNodeIndex)
{
    std::vector<uint32_t> result;

    parseBFS(startNodeIndex, [&](uint32_t index){
        result.push_back(index);
    });
    
    return result;
}

bool UndirectedGraph::areNodeAdjacent(uint32_t indexA, uint32_t indexB)
{
    for (uint32_t it : adjacenyList[indexA]) {
        if (indexB == it) {
            return true;
        }
    }

    return false;
}

bool UndirectedGraph::isPath(std::vector<int> nodeList)
{
    uint32_t index;
    uint32_t sz = nodeList.size();

    for (index = 0; index < sz - 1; ++index) {
        if (!areNodeAdjacent( nodeList[index], nodeList[index + 1] )) {
            return false;
        }
    }

    return true;
}

double UndirectedGraph::getEdgeValue(uint32_t indexA, uint32_t indexB)
{
    return edgesValues[{indexA, indexB}];
}