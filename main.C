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
#include "Serial.h"

//In the m-tuple test x^2 decreases as the number of
//elements in the array increases... I don't know if this is expected or not
//p-value trends towards 1. I'd expect it to be closer to 0.5?

//Main
int main(int argc, char **argv)
{
    //create gen
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 12);
    srand(time(NULL));

    //Create sample
    vecInt vec(10000,0);
    double chiTot = 0;
    int DoFTot = 0;

    //Set to 1 to only run once
    int maxIt = 100;
    for(int j = 0; j < maxIt; j++){

	if(j%10 == 0)
	    std::cout << "Loop iteration: " << j << std::endl;
	
	for(int i = 0; i < vec.size(); i++)
	    //vec[i] = dis(gen);
	    vec[i] = i%12+1;
	    //vec[i] = 1;
	
	//Test sample
	double chi = 0;
	int DoF = 0;
	
	Serial test(12, vec);
	
	test.test(chi, DoF);
	
	// std::cout << "X^2: " << chi << " DoF: " << DoF << std::endl;
	chiTot += chi;
	DoFTot = DoF;
    }
    
    std::cout << "X^2: " << chiTot/maxIt << " DoF: " << DoFTot << std::endl;
    return 0;
}

