#include <iostream>

#include "myfunctions.h"

/*
	Don't include the entire std library:
	using namespace std;
*/

// Just include the ones you need
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	int a=5;
	int b=10;
	int c=sumOfTwoNumbers(a, b);
	cout << "Hello World!";
	cout << "\n\nc = " << c << endl;
	cout << endl;
	
	string greet;
	cout << "What is your name ? ";
	getline(cin, greet);
	cout << "Thanks " << greet << endl;
	
	return 0;
}
