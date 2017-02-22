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
    //Inizialize chi and DoF
    //DoF is the size of the hand - 1, because there are size of hand options
    //for the number of repeat numbers (2 of a kind, 3, 4, etc)
    chi = 0;
    DoF = handSize - 1;
    
    //Create vector to hold expected number of times each type of hand appears:
    //aaaaa
    //aaaab
    //aaabb
    //aaabc
    //aabbc
    //aabcd
    //abcde
    //TODO:Figure out how to determine frequency
    vecInt expectedFreq = {1/std::pow(maxVal,4),
			   1/std::pow(maxVal,3) * (maxVal - 1)/maxVal};
		   
    //Create vector to hold number of times each hand appears.
    vecInt freq(7,0);
    //populate that vector
    for(int i = 0; i < sample.size(); i++)
    {
	//create a hand
        vecInt hand;
	for(int j = 0; j < handSize; j++)
	    hand.push_back(sample.at( (i+j) % sample.size() ) );

	//Check to see what kind of hand it is and
	//record it
	std::map<uint,uint> handMap;
	for(auto&& elem : hand)
	{
	    auto mapElem = handMap.find(elem);
	    if(mapElem == handMap.end())
		handMap.insert(std::pair<uint,uint>(elem,1));
	    else
		mapElem->second++;
	}
	
	//Get the frequency counts (ie (5), (4,1),(3,2),(3,1,1), etc
	bool foundHand = false;
	uint prevMax = 6;
	
	for(int i = 0; !foundHand; i++)
	{
	    uint maxFreq = 0;
	    for(auto&& pair : handMap)
		if(pair.second > maxFreq && pair.second <= prevMax)
		    maxFreq = pair.second;


            //If we've uniquily identified a hand, increase freq count
	    if(maxFreq >= 4)
	    {
		if(maxFreq >= 5)
		    freq.at(0)++;
		else
		    freq.at(1)++;
		foundHand = true;
	    }
	    else
	    {
		if(prevMax == 3 && maxFreq == 2)
		{
		    freq.at(2)++;
		    foundHand = true;
		}
		else if(prevMax == 3 && maxFreq == 1)
		{
		    freq.at(3)++;
		    foundHand = true;
		}
		else if(prevMax == 2 && maxFreq == 2)
		{
		    freq.at(4)++;
		    foundHand = true;
		}
		else if(prevMax == 2 && maxFreq == 1)
		{
		    freq.at(5)++;
		    foundHand = true;
		}
		else if(prevMax == 1 && maxFreq == 1)
		{
		    freq.at(6)++;
		    foundHand = true;
		}
	    }
	    prevMax = maxFreq;
	}
    }//Looped through all hands now

    //Calculate chi
    for(int i = 0; i < freq.size(); i++)
	chi += std::pow(freq[i] - expectedFreq[i],2)/expectedFreq[i];
    return true;
}
