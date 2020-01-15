#include "chromosome.h"
#include <cstring>
#include <cmath>

Chromosome::Chromosome()
{
    size = 0;
}

Chromosome::Chromosome(uint32_t size) : size(size)
{}

Chromosome& Chromosome::addGene(Gene gene)
{
    if (genes.size() >= size) {
        return *this;
    }

    genes.push_back(gene);

    return *this;
}


Chromosome::Chromosome(const Chromosome& obj)
{
    size = obj.size;

    if (!genes.empty()) {
        genes.clear();
    }

    for (auto it : obj.genes) {
        genes.push_back(it);
    }
}

void Chromosome::operator=(const Chromosome& obj)
{
    size = obj.size;
    
    if (!genes.empty()) {
        genes.clear();
    }
    
    for (auto it : obj.genes) {
        genes.push_back(it);
    }
}

uint32_t Chromosome::getSize()
{
    return size;
}

Gene Chromosome::at(uint32_t index)
{
    return genes[index];
}

void Chromosome::set(uint32_t index, const Gene& chr)
{
    if (index > genes.size()) {
        return;
    }

    genes[index] = chr;
}

void Chromosome::swap(uint32_t geneA, uint32_t geneB)
{
    std::swap(genes[geneA], genes[geneB]);
}