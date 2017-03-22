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
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <time.h>
#include "MTuple.h"
#include "Serial.h"
#include "Frequency.h"

using string = std::string;
int tests(vecInt& data);
int printHand(vecInt hand);
int loadData(vecInt& data);

int main(int argc, char **argv)
{
//    vecInt data{1,2,3,4,5,6,2,3,4,5};
    vecInt data;
//    MTuple tuple(3,6, data);

//    double chi;
//    int DoF;
//    tuple.test(chi, DoF);

//    std::cout << "X^2: " << chi << " DoF: " << DoF << std::endl;
    //Load in the data
    loadData(data);
    //Test the data
    return tests(data);
}

int loadData(vecInt& data)
{
    //create gen
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 12);

    int dataSize = 100;
    for(int i = 0; i < dataSize; i++)
	data.push_back(dis(gen));
    

    /*string fileLoc = "/home/adam/Documents/dice/test.csv";
    fileLoc = "/media/adam/DATA/DicePictures/Run3/labels.csv";

    std::ifstream file;
    file.open(fileLoc);
    if(!file.is_open())
	std::cout << "Can't open " << fileLoc << "!" << std::endl;

    string line;

    //Load in the data
    while(std::getline(file, line))
	if(line.find("#") == string::npos)
	    data.push_back(std::stoi(line));
    
    //print out the data
    //for( auto&& elem : data)
    //std::cout << elem << std::endl;
    */    
    return 0;
}

int printHand(vecInt hand)
{
    std::map<uint,uint> sortedHand;
    vecInt uniqueNum;

    //Create a map that contains <num, frequecny>
    //Create a vector containing unique numbers
    for(auto&& elem : hand)
    {
	if(!std::binary_search(uniqueNum.begin(), uniqueNum.end(), elem))
	    uniqueNum.push_back(elem);
	
	auto mapElem = sortedHand.find(elem);
	if(mapElem == sortedHand.end())
	    sortedHand.insert(std::pair<uint,uint>(elem,1));
	else
	    mapElem->second++;
    }
    
    //Print out sorted hand
    return 0;
}

//In the m-tuple test x^2 decreases as the number of
//elements in the array increases... I don't know if this is expected or not
//p-value trends towards 1. I'd expect it to be closer to 0.5?

//Main
int tests(vecInt& data)
{
    double chi = 0;
    int DoF = 0;

    //M-Tuple test
    MTuple tuple(3, 12, data);
    tuple.test(chi, DoF);
    std::cout << "3-tuple test: " << std::endl <<
	"X^2: " << chi << " DoF: " << DoF << std::endl;

    //Frequency test
    Frequency freq(12, data);
    freq.test(chi, DoF);
    std::cout << "Frequency: " << std::endl <<
	"X^2: " << chi << " DoF: " << DoF << std::endl;

    //Serial test
    Serial serial(12, data);
    serial.test(chi, DoF);
    std::cout << "Frequency: " << std::endl <<
	"X^2: " << chi << " DoF: " << DoF << std::endl;

    return 0;
}

