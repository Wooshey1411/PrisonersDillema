#include <iostream>
#include <fstream>
#include <regex>
#include "matrix.h"

inline unsigned int startHash = 201; // hash of CCC
inline int hashError = -1;

enum hashes{
    CCC = 201,
    CCD = 202,
    CDD = 203,
    DDD = 204
};

int hash(std::string_view str){
    size_t size = str.length();
    if(size != COUNT_OF_COLUMNS)
        return hashError;
    int res = 0;
    for (size_t i = 0; i < size; ++i) {
        if(str[i] != 'C' && str[i] != 'D')
            return hashError;
        res+=str[i];
    }
    return res;
}

DilemmaMatrix::DilemmaMatrix(){
    for (unsigned int i = 0; i < COUNT_OF_LINES; ++i) {
        auto* line = new unsigned int[COUNT_OF_COLUMNS];
        for (unsigned int j = 0; j < COUNT_OF_COLUMNS; ++j) {
            line[j] = 0;
        }
        _matrix[startHash+i] = line;
    }
}

void DilemmaMatrix::fillMatrixFromFile(const std::string& path){
    std::ifstream in;
    in.open(path);

    if(!in.is_open()) {
        _matrix[hashes::CCC][0]=7; _matrix[hashes::CCC][1]=7; _matrix[hashes::CCC][2]=7;
        _matrix[hashes::CCD][0]=3; _matrix[hashes::CCD][1]=3; _matrix[hashes::CCD][2]=9;
        _matrix[hashes::CDD][0]=0; _matrix[hashes::CDD][1]=5; _matrix[hashes::CDD][2]=5;
        _matrix[hashes::DDD][0]=1; _matrix[hashes::DDD][1]=1; _matrix[hashes::DDD][2]=1;
        return;
    }

    std::string line;
    auto buff = std::make_unique<unsigned int[]>(COUNT_OF_COLUMNS);
    std::string code = "AAA";
    std::regex reg(R"(((^|&, )(([C,D]{3})(\s+)(([0-9]{1,12}(\s+))){2}([0-9]{1,12})(\s*))|(#)(.*)(#))+$)");
    std::cmatch res;

    unsigned int parsed = 0;
    while (!in.eof()){
        std::getline(in,line);
        if(line.empty())
            continue;
        if(!std::regex_match(line.c_str(),res,reg)) // type of line: CCD 8   8  4
            throw std::runtime_error("DilemmaMatrix::fillMatrixFromFile: Bad matrix");

        if(line[0] == '#')
            continue;
        unsigned int pos = 0;
        for (unsigned int i = 0; i < COUNT_OF_COLUMNS; ++i) {
            code[i] = line[pos];
            pos++;
        }
        int codeHash = hash(code);
        if(codeHash < hashes::CCC || codeHash > hashes::DDD)
            throw std::runtime_error("DilemmaMatrix::fillMatrixFromFile: Bad matrix - impossible code"); // impossible code ?

        size_t lenOfLine = line.length();
        for (unsigned int i = 0; i < COUNT_OF_COLUMNS; ++i) {
            unsigned int num = 0;
            bool isParsed = false;
            while(true){
                if(lenOfLine == pos || (line[pos] == ' ' && isParsed))
                    break;
                if(line[pos] != ' ') {
                    num = num * 10 + (line[pos] - '0');
                    isParsed = true;
                }
                pos++;
            }
            buff[i] = num;
        }

        for (unsigned int i = 0; i < COUNT_OF_COLUMNS-1; ++i) { // C = C, D = D in columns
            for (unsigned int j = i+1; j < COUNT_OF_COLUMNS; ++j) {
                if(code[i] == code[j] && buff[i] != buff[j])
                    throw std::runtime_error("DilemmaMatrix::fillMatrixFromFile: Bad matrix - unequal values of code");
            }
        }

        for (unsigned int i = 0; i < COUNT_OF_COLUMNS; i++){ // sort for exclude permutations CDC,DCC -> CCD
            for (unsigned int j = COUNT_OF_COLUMNS - 1; j > i; j--) {
                if(code[j-1] > code[j])
                {
                    char temp = code[j-1];
                    code[j-1]=code[j];
                    code[j]=temp;
                    unsigned int num = buff[j-1];
                    buff[j-1]=buff[j];
                    buff[j]=num;

                }
            }
        }

        bool newLine = true;
        for (unsigned int i = 0; i < COUNT_OF_COLUMNS; ++i) { // unfilled line is 0 0 0
            if(_matrix[codeHash][i] != 0) {
                newLine = false;
                break;
            }
        }

        if(newLine){
            parsed++;
            for (unsigned int i = 0; i < COUNT_OF_COLUMNS; ++i) {
                _matrix[codeHash][i]=buff[i];
            }
        }else{ // case when we have CCC 3 3 3 and CCC 5 5 5
            for (unsigned int i = 0; i < COUNT_OF_COLUMNS; ++i) {
                if(_matrix[codeHash][i]!=buff[i])
                    throw std::runtime_error("DilemmaMatrix::fillMatrixFromFile: Bad matrix - no symmetry");
            }
        }


    }
    if(parsed != COUNT_OF_LINES)
        throw std::runtime_error("DilemmaMatrix::fillMatrixFromFile: Bad count of lines");
    in.close();

    // d0 > c0 > d1 > c1 > d2 > c2
    if(_matrix[hashes::CCD][2] <= _matrix[hashes::CCC][0] || // d0 <= c0
            _matrix[hashes::CCC][0]<= _matrix[hashes::CDD][2] || // c0 <= d1
            _matrix[hashes::CDD][2] <= _matrix[hashes::CCD][0] || // d1 <= c1
            _matrix[hashes::CCD][0] <= _matrix[hashes::DDD][0] || // c1 <= d2
            _matrix[hashes::DDD][0] <= _matrix[hashes::CDD][0]) // d2 <= c2
        throw std::runtime_error("DilemmaMatrix::fillMatrixFromFile: d0 > c0 > d1 > c1 > d2 > c2 - false");

    // 3 * c0 > 2 * c1 + d0
    if((3*_matrix[hashes::CCC][0]) <= (2*_matrix[hashes::CCD][0] + _matrix[hashes::CCD][2]))
        throw std::runtime_error("DilemmaMatrix::fillMatrixFromFile: 3 * c0 > 2 * c1 + d0 - false");

    // 3 * c0 > 2 * d1 + c2
    if((3*_matrix[hashes::CCC][0]) <= (2*_matrix[hashes::CDD][2] + _matrix[hashes::CDD][0]))
        throw std::runtime_error("DilemmaMatrix::fillMatrixFromFile: 3 * c0 > 2 * d1 + c2 - false");

    // 3 * c0 > 3 * d2
    if((3*_matrix[hashes::CCC][0]) <= (3*_matrix[hashes::DDD][0]))
        throw std::runtime_error("DilemmaMatrix::fillMatrixFromFile: 3 * c0 > 3 * d2 - false");

}

unsigned int DilemmaMatrix::getValue(std::string_view code, char type) {
    int lineHash = hash(code);
    if (lineHash == hashError || lineHash < hashes::CCC || lineHash > hashes::DDD)
        throw std::runtime_error("DilemmaMatrix::getValue: Line doesn't exists in matrix");
    if(type != 'C' && type != 'D')
        throw std::runtime_error("DilemmaMatrix::getValue: Wrong type");
    if ((type == 'C' && lineHash == hashes::DDD) || (type == 'D' && lineHash == hashes::CCC))
        throw std::runtime_error("DilemmaMatrix::getValue: For such type line doesn't exists");
    if(type == 'C')
        return _matrix[lineHash][0]; // in 0 pos always C if it not DDD
    else
        return _matrix[lineHash][2]; // in 2 pos always D if it not CCC
}

DilemmaMatrix::~DilemmaMatrix(){
    for (unsigned int i = 0; i < COUNT_OF_LINES; i++) {
        delete[] _matrix[startHash+i];
    }
}

