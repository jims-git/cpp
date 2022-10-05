#include <iostream>
#include "myfunctions.h"

// Don't include the entire std library:
// using namespace std;

// Just include the ones you need
using std::cin;
using std::cout;
using std::endl;
using std::string;

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
	
	
	string greet;
	cout << "What is your name ? ";
	getline(cin, greet);
	cout << "Thanks " << greet << endl;
	
	return 0;
}
