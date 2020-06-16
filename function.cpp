#include "function.h"
#include <iostream> 
using namespace std;
int op(vector<unsigned int> * theVec)
{
	//put vector size into a variable 
	int vecsize = theVec->size();
	//create vector to prevent function calls 
	unsigned int* vecData = theVec->data();

	int result = vecsize;

	for (unsigned int i = 0; i < vecsize; i += 2)
	{
		vecData[i] = (vecData[i] + 1) << 1;
		vecData[i + 1] = (vecData[i + 1] + 1) << 1;

		vecData[i] = vecData[i] - (vecData[i] >> 8 << 8);
		vecData[i + 1] = vecData[i + 1] - (vecData[i + 1] >> 8 << 8);
		vecData[i] = vecData[i] + vecData[i + 1];

		result = result + vecData[i] + vecData[i + 1];

		if (vecData[0] % 7 == 1)
		{
			vecData[i]++;
			result++;
		}
		//result++;
	}
	return result;
}