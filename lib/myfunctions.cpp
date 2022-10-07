#include <iostream>
#include <vector>
#include "myfunctions.h"

// using namespace std;

using std::cin;
using std::cout;
using std::endl;
using std::string;



// Function that returns the sum of two numbers
int sumOfTwoNumbers(int a, int b)
{
	return(a+b);
}


// VOID Pointers
// Allows the function to accept any datatype and cast it afterwards
void print(void *ptr, char type)
{
	switch(type)
	{
		// cast ptr to an int, and then dereference it
		case 'i': cout << *((int*)ptr) << endl; break; 
		
		// cast ptr to a char, and then dereference it
		case 'c': cout << *((char*)ptr) << endl; break; 
		
		default :cout << "Unknown or unimplemented data type." << endl;
	}
}




// Pointers to get multiple RETURNs from a function.
// pointers to min and max are passed in and can be 
// acceses from main.
void getMinAndMax(int *numbers, int size, int *min, int *max)
{
	*min = *(numbers);
	*max = *(numbers);
	for(int i=1 ; i<size ; i++)
	{
		if( *(numbers+i) > *max) *max = *(numbers+i);
		if( *(numbers+i) < *min) *min = *(numbers+i);
	}
}







// Function Pointers
bool ascendingCompare(int a, int b){ return a < b;}
bool descendingCompare(int a, int b){ return a > b;}
void customSort(vector<int>& numbersVector, bool(*compareFunctionPointer)(int,int))
{
	for( std::vector<int>::size_type startIndex = 0 ; startIndex < numbersVector.size() ; startIndex++)
	{
		int bestIndex = startIndex;
		for(std::vector<int>::size_type currentIndex = startIndex+1; currentIndex < numbersVector.size(); currentIndex++)
		{
			// We are doing comparison here
			if(compareFunctionPointer(numbersVector[currentIndex], numbersVector[bestIndex]))
				bestIndex = currentIndex;
		}
		swap(numbersVector[startIndex], numbersVector[bestIndex]);
	}
}
void sortAscending(vector<int>& numbersVector)
{
	for( std::vector<int>::size_type startIndex = 0 ; startIndex < numbersVector.size() ; startIndex++)
	{
		int bestIndex = startIndex;
		for(std::vector<int>::size_type currentIndex = startIndex+1; currentIndex < numbersVector.size(); currentIndex++)
		{
			// We are doing comparison here
			if(ascendingCompare(numbersVector[currentIndex], numbersVector[bestIndex]))
				bestIndex = currentIndex;
		}
		swap(numbersVector[startIndex], numbersVector[bestIndex]);
	}
}
void sortDescending(vector<int>& numbersVector)
{
	for( std::vector<int>::size_type startIndex = 0 ; startIndex < numbersVector.size() ; startIndex++)
	{
		int bestIndex = startIndex;
		for(std::vector<int>::size_type currentIndex = startIndex+1; currentIndex < numbersVector.size(); currentIndex++)
		{
			// We are doing comparison here
			if(descendingCompare(numbersVector[currentIndex], numbersVector[bestIndex]))
				bestIndex = currentIndex;
		}
		swap(numbersVector[startIndex], numbersVector[bestIndex]);
	}
}
void printNumbers(vector<int> &numbersVector)
{

	// get a warning if you try to compare int with vector.size()
	// vector.size() is std::vector<int>::size_type
	// aka ‘long unsigned int’
	for(std::vector<int>::size_type i=0 ; i < numbersVector.size() ; i++)
	{
		cout << numbersVector[i] << ' ';
	}
}












