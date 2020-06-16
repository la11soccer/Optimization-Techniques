/*//function calls take a long time
{
for (int i = 0; i < theVec->Size; i++)
{
	sum++
}

CHANGE TO
int size = theVec.size();
for (int i = 0; i < size; i++)
{
	sum++
}

fuxntioncall you ahve to allocat memory on stack, allocate memory for that etc then go back to code
}

///double whats in the loop and only run it half as many times (loop unrolling) 
{
	int sum = 0;
	int size = theVec->size();
	for (int i = 0; i < size; i++)
	{
		sum++;//this is not just a single instruction, you are have many instructions because you have to check the size, increase the sum, and do i++
		//this is the for lopp overhead time
	}
	CHANGE TO
	for (int i = 0; i < size; i+=2)
	{
		sum++;
		sum++;
		//when you do this, you are only executing the over head of the for loop half the time.
	}

}

{
	int sum = 0;
	int size = theVec->size();
	for (int i = 0; i < size; i++)
	{
		sum += theVec->operator[](i);

	}
	

	for (int i = 0; i < size; i += 2)
	{
		unsigned int t = data[i];//this is slower with the unisgned int int he for loop because now you are allocating this every time you go through the for loop
		sum++;
		sum++;
	}

	//bit shift tho the left multiply by 2 bit shift right you are dividing by teo



	//-------------------------------------
	//these operation require each result be saved in a variable, imporve by replacing all intermediate variables
	for (int i = 0; i < size; i += 2)
	{
		sum = data[i];
		sum = sum + sum;
		sum -= sum;
		sum += 6;

	}
	CHAGNES TO 

		for (int i = 0; i < size; i += 2)
		{
			sum = data[i] + data[i] - 5 +6;
			

		}
}


//this checks to see if sum is even, if it is it will add 1

unsigned int* data = theVec->data();

for(int i=0; i<size; i++)
{
	sum = 1000;
	if (sum % 2 == 0)
	{
		sum++;
	}
}

for (int i = 0; i < size; i++)
{
	sum = 1000;
	sum = sum | 0x1; // using bitwise operatior
}*/

#include <iostream>
#include <chrono>
#include <vector>
#include "function.h"
using namespace std;

/*
int bitshift()
{
	unsigned int testint = 256;
	testint = testint >> 8;
	
	cout << "Here is test bit shift" << testint << "value should be 1\n";
	testint = testint << 8;
	cout << "we should be back at 256" << testint << "\n"; 
	return 0;
}*/
int original(vector<unsigned int> * theVec)
{
	for (unsigned int i = 0; i < theVec->size(); i++)
	{
		theVec->at(i) = theVec->at(i) + 1;///
	}
	
	for (unsigned int i = 0; i < theVec->size(); i++)
	{
		theVec->at(i) = theVec->at(i) * 2;///
	}
	for (unsigned int i = 0; i < theVec->size(); i++)
	{
		if (theVec->at(i) > 255)///
		{
			int amountToRemove = theVec->at(i) / 256;
			amountToRemove = amountToRemove * 256;theVec->at(i) = theVec->at(i) - amountToRemove;
		}
	}
	for (unsigned int i = 0; i < theVec->size(); i+=2)
	{
		theVec->at(i) = theVec->at(i) + theVec->at(i+1);///
	}
	for (unsigned int i = 0; i < theVec->size(); i++)
	{
		if(theVec->at(i) %2 == 1)theVec->at(i) = theVec->at(i) +1;//
	}
	for (unsigned int i = 0; i < theVec->size(); i ++)
	{
		if (theVec->at(0) % 7 == 1)
			theVec->at(i) = theVec->at(i) + 1;///
	}
	int result = 0;
	for (unsigned int i = 0; i < theVec->size(); i++)
	{
		result += theVec->at(i);//
	}
	result = theVec->size();
	for (unsigned int i = 0; i < theVec->size(); i++)
	{
		result+= theVec->at(i);
	}
	return result;
}

int main(int argc, char** argv)
{
	int a, b; 
	srand(clock()); 
	long long originaltime = 0, optime = 0; 
	//////////////
	//int testint = bitshift();
	for (int z = 0; z < 100; z++) 
	{
		int amountOfData = rand() % 10000 + 10000; 
		if (amountOfData % 2 == 1) 
		{ 
			amountOfData++; 
		}
		vector<unsigned int> data; 
		for (int i = 0; i < amountOfData; i++) 
		{ 
			data.push_back(rand()); 
		}
		vector<unsigned int> data2 = data;
		//time counting from https://www.techiedelight.com/measure-elapsed-time-program-chrono-library/
		auto start = chrono::steady_clock::now();
		a = original(&data);
		auto end = chrono::steady_clock::now();
		//cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
		originaltime += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
		start = chrono::steady_clock::now();
		b = op(&data2);
		end = chrono::steady_clock::now();
		optime+= chrono::duration_cast<chrono::nanoseconds>(end - start).count();
		//cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
		if (a != b){cout << "answers do not match\n";}
	}
	cout << "original time" << originaltime << endl; 
	cout << "optimized time" << optime << endl; 
	std::cin.ignore();
}