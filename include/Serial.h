///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                            Copyright (C) 2017                             //
//                    Adam Anthony : All rights reserved                     //
//                                                                           //
//     This source code is licensed under the GNU GPL v3.0.You have the      //
//     right to modify and/or redistribute this source code under the terms  //
//     specified in the license, which may be found online at                //
//     http://www.gnu.org/licenses.                                          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

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
