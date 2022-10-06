#include <iostream>
#include <vector>
#include "myfunctions.h"

// Don't include the entire std library:
using namespace std;

// Just include the ones you need
/*
using std::cin;
using std::cout;
using std::endl;
using std::string;
*/

int main() {
	int a=5;
	int b=10;
	int c=sumOfTwoNumbers(a, b);
	
	int *pA = &a;
	int size = 5;
	int luckyNumbers[size] = {2,3,5,7,9};

	
	auto result = (10 <=> 20) > 0;
	cout << "Result = " << result << endl;
	
	cout << "\n\nHello World!";
	cout << "\n\nc = " << c << endl;
	cout << endl;
	
	cout << "variable a's value          = " << a << endl;
	cout << "variable a's memory address = " << &a << endl;
	cout << "pA is pointing to address   = " << pA << endl;
	cout << "*pA to get the value        = " << *pA << endl;
	cout << endl;
	
	cout << "luckyNumbers memory address = " << luckyNumbers << endl;
	cout << "&luckyNumbers[0]            = " << &luckyNumbers[0] << endl;
	cout << "luckyNumbers[2]    = " << luckyNumbers[2] << endl;
	cout << "*(luckyNumbers+2)  = " << *(luckyNumbers+2) << endl;
	cout << "luckyNumbers[" << size << "] = { ";
	for(int i=0 ; i<size ; i++)
		cout << luckyNumbers[i] << "   ";
	cout << "}" << endl;
	int min, max;
	getMinAndMax(luckyNumbers, size, &min, &max);
	cout << "The smallest value is " << min << endl;
	cout << "The largest value is  " << max << endl;
	cout << endl;
	
	int v;
	int *ptr = &v; // *ptr equals the address of the variable v
	*ptr = 7;      // at te address ptr store the value 7
	cout << "v = " << v << endl;
	cout << endl;
	
	// VOID Pointers
	int number = 8675309;
	char letter = 'j';
	double pi = 3.14;
	print(&number, 'i');
	print(&letter, 'c');
	print(&pi, 'd');
	cout << endl;
	
	/*
	// Dynamic Arrays
	// Make sure to free the memory when finished
	int dynamicSize;
	cout << "What size is the array ? ";
	cin >> dynamicSize;
	int *dynArray = new int[dynamicSize];
	for(int i=0;i<dynamicSize;i++)
	{
		cout << "Array[" << i << "] = ";
		cin >> dynArray[i];
	}
	for(int i=0;i<dynamicSize;i++)
	{
		cout << *(dynArray+i) << "  ";
	}
	cout << endl;
	cout << endl;
	delete[]dynArray;
	dynArray=NULL; // safety 
	*/
	
	
	// Multi dim dynamic array
	int rows, cols;
	do
	{
		cout << "How many rows, cols (min rows=5 cols=6)? ";
		cin >> rows >> cols;
	}while( rows <= 4 || cols <= 5);
	// create a pointer to an array of pointers
	int **table = new int*[rows];
	for(int i=0;i<rows;i++)
	{
		table[i]=new int[cols];
		// clear this array setting evertything to zero
		for(int j=0;j<cols;j++) table[i][j] = 0;
	}
	table[4][5] = 345;
	cout << "table[4][5] = 345;" << endl;
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++) cout << table[i][j] << "  ";
		cout << endl;
	}
	// finished with array of arrays of int[] so free
	for(int i=0;i<rows;i++)
	{
		delete table[i];
	}
	delete[] table;
	// all memory has been freed, so no point in saving the address for safety
	table = NULL;
	cout << endl;
	
	
	/* 
		Function Pointers
		To create a function pointer:
		1. Give it a name   : funcPtr
		2. add the asterisk : *funcPtr
		3. wrap it in parens: (*funcPtr)
		4. return type goes first : int(*funcPtr)
		5. add parameters in parens : int(*funcPtr)(int, int)
		6. set it equal to a function : int(*funcPtr)(int, int) = sumOfTwoNumbers;
		Notice that the function name is the address to the function, so the
		function pointer is just pointing to the functions address.
	*/
	int(*funcPtr)(int, int) = sumOfTwoNumbers;
	cout << "funcPtr(3, 5) = ";
	cout << funcPtr(3, 5);
	cout << endl << endl;
	
	vector<int> myNumbers = { 2,5,1,3,6,4 };
	sortAscending(myNumbers);
	printNumbers(myNumbers);
	cout << endl << endl;
	sortDescending(myNumbers);
	printNumbers(myNumbers);
	cout << endl << endl;
	cout << "customSort()" << endl;
	bool(*ascend)(int,int) = ascendingCompare;
	bool(*descend)(int,int)= descendingCompare;
	customSort(myNumbers, ascend);
	printNumbers(myNumbers);
	cout << endl << endl;
	customSort(myNumbers, descend);
	printNumbers(myNumbers);
	cout << endl << endl;
	
	
	
	
	cout << endl << endl;
	string greet;
	cout << "What is your name ? ";
	cin.ignore(); // ignores \n that cin >> str has lefted (if user pressed enter key)
	getline(cin, greet);
	cout << "Thanks " << greet << endl;
	
	return 0;
}
