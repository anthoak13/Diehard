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


#include "Serial.h"


Serial::Serial(const uint maxInt, const vecInt &sampleIn) :
    sample(sampleIn), helper(maxInt)
{
    maxVal = maxInt;
}

bool Serial::test(double &chi, int &DoF)
{
    vecDouble expectedP(maxVal, 1/(double)maxVal);

    return test(chi, DoF, expectedP);
}
bool Serial::test(double &chi, int &DoF, const vecDouble& p)
{
    chi = 0;
    DoF = maxVal * (maxVal - 1);

    //Create vector to hold number of times each pair appears (want overlapping 2-tuples)
    
    vecInt freq(maxVal*maxVal,0);

    //Populate that vector remebering to shift to a zero index
    for(int i = 0; i < sample.size() - 1; i++)
    {
	vecInt tuple = {sample[i] - 1, sample[ i+ 1] - 1};
	freq.at( helper.to1Dim(tuple) )++;
    }
    freq.at(helper.to1Dim(vecInt{sample.back()-1, sample.front()-1}));

    //Calculate the x^2 test statistic
    for(int i = 0; i < freq.size(); i++)
    {
	vecInt index = helper.toMDim(i,2);
	double expVal = p.at(index[0])*p.at(index[1])*sample.size();
	chi += std::pow(freq[i] - expVal,2)/expVal;
    }

    //std::cout << "X^2: " << chi << " DoF: " << DoF << std::endl;

    return true;
			   
}
