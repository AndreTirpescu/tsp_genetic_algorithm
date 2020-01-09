#include "tspformatreader.h"

TspFormatReader::TspFormatReader(const char *path) 
{
    fin.open(path);
}

void TspFormatReader::readHeaderInfo(uint32_t headerSize)
{
    std::string contentType;
    std::string dp;
    std::string info;
    uint32_t    index;

    for (index = 0; index < headerSize; ++index) {
        fin >> contentType;
        fin >> dp;
        std::getline(fin, info);

        headerDataMap[contentType] = info;
    }
}

std::string TspFormatReader::getHeaderDataFor(HeaderInfoData infoKey) const
{
    return headerDataMap.at(KNOWN_HEADER_INFO.at(infoKey));
}

// EUC_2D strategy
// @TODO INJECT STRATEGY FOR DATA
std::vector< std::pair<float, float> > TspFormatReader::readData()
{
    uint32_t    nodeCount = atoi(getHeaderDataFor(HEADER_INFO_DATA_DIMENSION).c_str());
    uint32_t    index;
    uint32_t    nodeIndex;
    float       nodeIndexX;
    float       nodeIndexY;
    std::string dummy;
    std::vector< std::pair<float, float> > result(nodeCount + 1);

    fin >> dummy;
    for (index = 0; index < nodeCount; ++index) {
        
        fin >> nodeIndex;
        fin >> nodeIndexX >> nodeIndexY;

        result[nodeIndex] = {nodeIndexX, nodeIndexY};
    }

    return result;
}