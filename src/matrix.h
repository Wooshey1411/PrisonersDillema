#include <map>

inline const unsigned int countOfLines = 4;
inline const unsigned int countOfColumns = 3;

class DilemmaMatrix{
private:
    std::map <unsigned int, unsigned int*> matrix;
public:
    DilemmaMatrix();
    ~DilemmaMatrix();
    unsigned int getValue(std::string_view code, char type);
    void fillMatrixFromFile(const std::string& path);
};