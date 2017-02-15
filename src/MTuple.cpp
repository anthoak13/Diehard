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


//MTuple implimentation
//Adam Anthony
//2/6/2017

#include "MTuple.h"

MTuple::MTuple(const uint mIn, const uint maxIn,
	       const vecInt &sampleIn) :
    sample(sampleIn) //need to use list to initialize const properly
{
    
    m = mIn < 3 ? 3 : mIn;
    maxVal = maxIn;
}

bool MTuple::test(double &chi, int &DoF)
{
    vecDouble p;
    for(int i = 0; i < maxVal; i++)
	p.push_back(1/(double)maxVal);
    for(auto&& elem : p ) std::cout << elem << " " ;
    std::cout << std::endl;
    return test(chi,DoF,p);
}

bool MTuple::test(double &chi, int &DoF, const vecDouble& p)
{
    //1 refers to higher order sum (ie Q3)
    //2 refers to lower order sum (ie Q2)
    double chi1 = 0;
    double chi2 = 0;

    //Create vectors to hold number of times each tuple appears
    vecInt w1(std::pow(maxVal,m),0);
    vecInt w2(std::pow(maxVal,m-1),0);

    
    //populate w1
    for(int i = 0; i < sample.size(); i++)
    {
	//create an mtuple.
        vecInt val;
	//decrease the sample by one because functions assume zero index
	for(int j = 0; j < m; j++)
	    val.push_back(sample[(i+j) % sample.size()] - 1);
	
	//increase w1[tuple].
	/*for(auto&& elem : val)
	    std::cout << elem << " ";
	std::cout << std::endl;
	std::cout << to1Dim(val) << std::endl;*/
	w1.at(to1Dim(val))++;
    }

    //populate w2
    for(int i = 0; i < sample.size(); i++)
    {
	//create an mtuple.
        vecInt val;
	for(int j = 0; j < m-1; j++)
	    val.push_back(sample[(i+j) % sample.size()] - 1);
	
	//increase w2[tuple].
	//for(auto&& elem : val)
	//    std::cout << elem << " ";
	//std::cout << std::endl;
	w2.at(to1Dim(val))++;
    }

    //Calculate the ch1 metric
    for(int i = 0; i < w1.size(); i++)
    {
	//If the tuple was never recorded, continue
	if(w1[i] == 0)
	{
	    chi1++;
	    continue;
	}

	vecInt tuple = toMDim(i,m);
	double mu = sample.size();
	for(auto&& elem : tuple)
	    mu *= p[elem];

	chi1 += (w1[i] - mu)*(w1[i] - mu)/mu;
    }
    std::cout << "Sample: " << sample.size() << std::endl;

    //Calculate the chi2 metric
    for(int i = 0; i < w2.size(); i++)
    {
	//If the tuple was never recorded, continue
	if(w2[i] == 0)
	{
	    chi2++;
	    continue;
	}

	vecInt tuple = toMDim(i,m-1);
	double mu = sample.size();
	for(auto&& elem : tuple)
	    mu *= p[elem];

	chi1 += (w2[i] - mu)*(w2[i] - mu)/mu;
    }

    chi = chi1-chi2;
    DoF = w1.size() - w2.size();
	

    //Test toMDim
    /*std::cout << to1Dim(toMDim(0,4)) << std::endl;
    std::cout << to1Dim(toMDim(511,4)) << std::endl;
    std::cout << to1Dim(toMDim(412,4)) << std::endl;
    std::cout << to1Dim(toMDim(325,4)) << std::endl;
    */
    return true;
}

//Code turns 1D index into an array of the indices for an MDim array
vecInt MTuple::toMDim(int index, int M)
{
    // std::cout << index << " in " << m << " dim => ";

    vecInt ret;
    for(int dim = M; dim > 2; dim--)
    {
	ret.push_back(index / std::pow(maxVal,dim - 1) );
	index -= ret.back()*std::pow(maxVal,dim - 1);
    }
    ret.push_back(index / maxVal);
    ret.push_back(index % maxVal);

    //for(auto&& elem : ret)
//	std::cout << elem <<  " ";
    //  std::cout << std::endl;
    return ret;
}

//Function returns the 1D equivalent of a m-dim array
int MTuple::to1Dim(vecInt index)
{
    int ret = 0;
    int M = index.size();
    for(int i = 0; i < M; i++)
	ret += index[i]*std::pow(maxVal,M-1-i);

    return ret;
}
