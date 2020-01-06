#include "chromosome.h"
#include <cstring>
#include <cmath>

#ifdef GENETIC_DEBUG
    #include <iostream>
#endif

Chromosome::Chromosome()
{
    size = 0;
}

Chromosome::Chromosome(uint32_t size) : size(size)
{}

Chromosome& Chromosome::addGene(Gene gene)
{
    if (genes.size() >= size) {
#ifdef GENETIC_DEBUG
        std::cout << "Cannot add gene\n";
#endif
        return *this;
    }

    genes.push_back(gene);

    return *this;
}

uint32_t Chromosome::getSize()
{
    return size;
}

void Chromosome::operator=(const Chromosome& ob)
{
    size = ob.size;
    genes.clear();
    for (auto it : ob.genes) {
        genes.push_back(it);
    }
}

Gene Chromosome::at(uint32_t index)
{
    if (index > size) {
#ifdef GENETIC_DEBUG
        std::cout << "Index greater than currently set\n";
#endif
    }

    return genes[index];
}

void Chromosome::set(uint32_t index, const Gene& chr)
{
    if (index > genes.size()) {
#ifdef GENETIC_DEBUG
        std::cout << "Index greater than currently set\n";
#endif

        return;
    }

    genes[index] = chr;
}