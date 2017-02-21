#include "ArrayHelper.h"


ArrayHelper::ArrayHelper(uint maxValIn)
{
    maxVal = maxValIn;
}

//Code turns 1D index into an array of the indices for an MDim array
vecInt ArrayHelper::toMDim(int index, int M) const
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
int ArrayHelper::to1Dim(vecInt index) const
{
    /*//Code to print out helpful info
    std::cout << "Trying to turn: (";
    for(auto&& t : index) std::cout << t << " ";
    std::cout << ") into 1 dim with max val: " << maxVal << " ";
    */
    int ret = 0;
    int M = index.size();
    for(int i = 0; i < M; i++)
	ret += index[i]*std::pow(maxVal,M-1-i);

    //std::cout << ret << std::endl;
    return ret;
}
