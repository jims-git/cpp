#include <iostream>

#include "myfunctions.h"

/*
	Don't include the entire std library:
	using namespace std;
*/

// Just inclue the ones you need
using std::cin;
using std::cout;
using std::endl;

int main() {
	int a=5;
	int b=10;
	int c=sumOfTwoNumbers(a, b);
  cout << "Hello World!";
  cout << "\n\nc = " << c << endl;
  cout << endl;
  return 0;
}
