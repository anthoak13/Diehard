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



//Entry point for program
#include <vector>
#include <iostream>
#include <cstdlib>
#include <random>
#include <time.h>
#include "MTuple.h"


//Main
int main(int argc, char **argv)
{
    //create gen
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 8);
    srand(time(NULL));
    
    vecInt vec(1000000,0);
    for(int i = 0; i < vec.size(); i++)
	vec[i] = 1 + rand() % 8;
    double chi = 0;
    int DoF = 0;
    MTuple test(3, 8, vec);
    test.test(chi, DoF);

    std::cout << "X^2: " << chi << " DoF: " << DoF << std::endl;
    return 0;
}

