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

#ifndef MTUPLE_H
#define MTUPLE_H

#include <iostream>
#include <cstdint>
#include <vector>
#include <cmath>
#include "ArrayHelper.h"

using uint = unsigned int;
using vecInt = std::vector<int>;
using vecDouble = std::vector<double>;

//Class definition
class MTuple
{
    
private:
    uint m;
    uint maxVal;
    const vecInt &sample;
    ArrayHelper help;
    
public:
    MTuple(const uint tupleSize, const uint maxInt, const vecInt &sampleIn);
    bool test(double &chi, int &DoF, const vecDouble& probabilites);
    bool test(double &chi, int &DoF);
    
};
#endif 
