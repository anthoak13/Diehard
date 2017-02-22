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
