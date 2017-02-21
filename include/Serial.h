// Marsaglia M-Tuple Test
// Overplapping M-Tuple test described in Marsaglia's keynote.
// Based in the implimetation in DIEHARDER.
// Adam Anthony
// 2/6/2017

#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>
#include <cstdint>
#include <vector>
#include <cmath>
#include "ArrayHelper.h"

using uint = unsigned int;
using vecInt = std::vector<int>;
using vecDouble = std::vector<double>;

//Class definition
class Serial
{
    
private:
    uint maxVal;
    const vecInt &sample;
    ArrayHelper helper;

    
public:
    Serial(const uint maxInt, const vecInt &sampleIn);
    bool test(double &chi, int &DoF);
    bool test(double &chi, int &DoF, const vecDouble& p);
    
};
#endif 
