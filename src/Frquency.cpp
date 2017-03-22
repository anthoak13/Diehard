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


#include "Frequency.h"


Frequency::Frequency(const uint maxInt, const vecInt &sampleIn) :
    sample(sampleIn), helper(maxInt)
{
    maxVal = maxInt;
}

bool Frequency::test(double &chi, int &DoF)
{
    vecDouble expectedP(maxVal, 1/(double)maxVal);

    return test(chi, DoF, expectedP);
}


bool Frequency::test(double &chi, int &DoF, const vecDouble& p)
{
    chi = 0;
    DoF = maxVal -1;

    //Create vector to store the number of times each number appears
    //and populate it
    vecInt freq(maxVal,0);
    for(auto&& elem : sample)
	freq[elem - 1]++;

    //Calculate the x^2 test statistic
    for(int i = 0; i < freq.size(); i++)
    {
	double expVal = p[i]*sample.size();
	chi += std::pow(freq[i] - expVal,2)/expVal;
    }

    //std::cout << "X^2: " << chi << " DoF: " << DoF << std::endl;
    //Print out the frequencies
    for(int i = 0; i < freq.size(); i++)
	std::cout << i+1 << ": " << freq[i] << " ";
	std::cout << std::endl;
    return true;
			   
}
