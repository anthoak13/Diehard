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

#include "Poker.h"

Poker::Poker(const uint handIn, const uint maxIn,
	       const vecInt &sampleIn) :
    sample(sampleIn), help(maxIn)//need to use list to initialize const properly
{
    
    //handSize = handIn < 5 ? 5 : handIn;
    handSize = 5;
    maxVal = maxIn;
}

bool Poker::test(double &chi, int &DoF)
{
    vecDouble p;
    for(int i = 0; i < maxVal; i++)
	p.push_back(1/(double)maxVal);

    //Print out calculated probabilities
//    for(auto&& elem : p ) std::cout << elem << " " ;
//    std::cout << std::endl;
    return test(chi,DoF,p);
}

bool Poker::test(double &chi, int &DoF, const vecDouble& p)
{
    //Inizialize chi
    chi = 0;
    
    //Create vector to hold expected number of times
    //each type of hand appears:
    //aaaaa
    //aaaab
    //aaabb
    //aaabc
    //aabbc
    //aabcd
    //abcde
    //also find the hands that should be grouped together.
    vecDouble expectedFreq = {1.0/20736,
			      55.0/20736,
			      55.0/10368,
			      275.0/5184,
			      275.0/3456,
			      275.0/576,
			      55.0/144};
    //Calculate the expected frequencies and
    //the number of groups to combine to reach required
    //minimum of 5 per catagory
    int smallestFreq = 0;
    int numToGroup = -1;
    for(int i = 0; i < expectedFreq.size(); i++)
    {
	expectedFreq.at(i) *= sample.size()/5;
	smallestFreq += expectedFreq.at(i);
	if(smallestFreq >= 5 && numToGroup < 0)
	    numToGroup = i;
    }
    std::cout << "Grouping first " << numToGroup << std::endl;
    DoF = 7 - numToGroup - 1;
    
		   
    //Create vector to hold number of times each hand appears.
    vecInt freq(7,0);
    //populate that vector
    for(int i = 0; i < sample.size(); i+=5)
    {
	//create a hand
        vecInt hand;
	for(int j = 0; j < handSize; j++)
	    hand.push_back(sample.at( (i+j) % sample.size() ) );
	
	//Group the hand by number
	std::map<uint,uint> handMap;
	for(auto&& elem : hand)
	{
	    auto mapElem = handMap.find(elem);
	    if(mapElem == handMap.end())
		handMap.insert(std::pair<uint,uint>(elem,1));
	    else
		mapElem->second++;
	}

	//Print out the hand
	/*std::cout << "At hand " << i << " of " << sample.size()
		  << std::endl;
	for(auto&& elem : handMap)
	    std::cout << elem.first
		      << " occurs " << elem.second
		      << " times." << std::endl;*/
	

	//Take hand and create a sorted vector containing the
	//number of times each number appears, is (1,1,3) (1,2,2) etc
	std::vector<ubyte> numFreq;
	for(auto&& elem : handMap)
	    numFreq.push_back(elem.second);
	std::sort(numFreq.begin(), numFreq.end());

	/* //Print out hand freq
	std::cout << i << ": ";
	for(auto&& elem : numFreq)
	    std::cout << (int)elem << " ";
	std::cout << std::endl;*/

	//Identify hand, and increase the frequency count
	bool foundHand = false;
	for(int j = 0; !foundHand && j < numFreq.size(); j++)
	{
	    if(numFreq.at(j) == 2)
	    {
		if(j == 0)
		    freq.at(2)++;
		if(j == 1)
		    freq.at(4)++;
		if(j == 3)
		    freq.at(5)++;
		foundHand = true;
	    }

	    if(numFreq.at(j) == 3)
	    {
		freq.at(3)++;
		foundHand = true;
	    }
	    
	    if(numFreq.at(j) == 4)
	    {
		freq.at(1)++;
		foundHand = true;
	    }

	    if(numFreq.at(j) == 5)
	    {
		freq.at(0)++;
		foundHand = true;
	    }
	}

	if(!foundHand)
	    freq.at(6)++;
		
    }//Looped through all hands now

    
    std::cout << "Frequencies" << std::endl;
    for(int i = 0; i < freq.size(); i++)
	std::cout << freq[i] << " " << expectedFreq[i] << std::endl;
    

    
    //combine groups
    for(int i = 0; i < numToGroup; i++)
    {
	freq[numToGroup] += freq[i];
	freq[i] = 0;
	expectedFreq[numToGroup] += expectedFreq[i];
	expectedFreq[i] = 0;
    }

    /*
    std::cout << "Adjusted Frequencies" << std::endl;
    for(int i = 0; i < freq.size(); i++)
	std::cout << freq[i] << " " << expectedFreq[i] << std::endl;
    */


    //Calculate chi
    for(int i = numToGroup; i < freq.size(); i++)
	chi += std::pow(freq[i] - expectedFreq[i],2)/expectedFreq[i];
    return true;
}
