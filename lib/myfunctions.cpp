#include <iostream>
#include "myfunctions.h"

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
