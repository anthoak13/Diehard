

//Entry point for program
#include <vector>
#include <iostream>
#include <cstdlib>

//function delacatations
int kperm(std::vector<int> v, int voffset);

//Main
int main(int argc, char **argv)
{
    srand(0);
    std::vector<int> perm (120);
    for(int i = 0; i < 1000; i++)
    {
	std::vector<int> v = {rand(),rand(),rand(),rand(),rand()};
	perm[kperm(v, 0)]++;
    }

    //Print
    for(auto&& n : perm)
	std::cout << n << std::endl;

//1701243281 1193353426 380509317 200011735 548048628 
    std::vector<int> v = {5,4,2,1,3};
    perm[kperm(v, 0)]++;
    
    return 0;
}


int kperm(std::vector<int> v, int voffset)
{
    int i, j, k, max;
    std::vector<int> w = v;
    int pindex,  uret, tmp;

    //copy v;
    for(i=0; i < v.size(); i++)
    {
	j = (i+voffset)%5;
	w[j] = v[j];
    }

    for(auto&& n : w)
	std::cout << n << " ";
    std::cout << std::endl;
    std::cout << "Permutations = " << std::endl;

    pindex = 0;
    for(i = 4; i > 0; i--)
    {
	max = w[0];
	k = 0;
	for (j=1; j <= i; j++)
	{
	    if(max <= w[j])
	    {
		max = w[j];
		k = j;
	    }
	}

	pindex = (1+i)*pindex + k;
	
	//Swap i and k
	tmp = w[i];
	w[i] = w[k];
	w[k] = tmp;

	std::cout << "Swapped " << i << " and " << k << std::endl;
	for(auto&& n : w)
	    std::cout << n << " ";
	std::cout << std::endl;

    }

    //finished generating permutations
    std::cout << " => " << pindex << std::endl;

    return pindex;
}
