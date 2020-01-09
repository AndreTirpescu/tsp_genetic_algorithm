#ifndef TSPFORMAT_READER_H
#define TSPFORMAT_READER_H

#include <string>
#include <fstream>
#include <map>
#include <vector>

// http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/index.html

enum HeaderInfoData
{
    HEADER_INFO_DATA_UNKNOWN,
    HEADER_INFO_DATA_NAME,
    HEADER_INFO_DATA_COMMENT,
    HEADER_INFO_DATA_TYPE,
    HEADER_INFO_DATA_DIMENSION,
    HEADER_INFO_DATA_EDGE_WEIGHT_TYPE
};

class TspFormatReader
{
public:
    TspFormatReader(const char* filePath);

    void readHeaderInfo(uint32_t headerSize);

    std::vector< std::pair<float, float> > readData();

    std::string getHeaderDataFor(HeaderInfoData infoKey) const;

private:
    std::ifstream   fin;
    std::map<std::string, std::string> headerDataMap;

    const std::map<HeaderInfoData, std::string> KNOWN_HEADER_INFO = {
        {HEADER_INFO_DATA_NAME,                 "NAME"},
        {HEADER_INFO_DATA_COMMENT,              "COMMENT"},
        {HEADER_INFO_DATA_TYPE,                 "TYPE"},
        {HEADER_INFO_DATA_DIMENSION,            "DIMENSION"},
        {HEADER_INFO_DATA_EDGE_WEIGHT_TYPE,     "EDGE_WEIGHT_TYPE"}
    };
};

#endif