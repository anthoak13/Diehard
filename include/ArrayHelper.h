#ifndef ARRAYHELPER_H
#define ARRAYHELPER_H

#include <vector>
#include <cmath>
#include <iostream>

using uint = unsigned int;
using vecInt = std::vector<int>;
using vecDouble = std::vector<double>;

class ArrayHelper
{
    uint maxVal;

public:
    ArrayHelper(uint maxVal);
    vecInt toMDim(int index, int M) const;
    int to1Dim(vecInt index) const;

};

#endif
