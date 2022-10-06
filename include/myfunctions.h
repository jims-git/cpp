using namespace std;


// Header Guard
#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H




// Function that returns the sum of two numbers
int sumOfTwoNumbers(int a, int b);


// VOID Pointers
void print(void *ptr, char type);


// Pointers to get multiple RETURNs from a function
void getMinAndMax(int *numbers, int size, int *min, int *max);



// Function Pointers
bool ascendingCompare(int a, int b);
bool descendingCompare(int a, int b);
void customSort(vector<int>& numbersVector, bool(*compareFunctionPointer)(int,int));
void sortAscending(vector<int> &numbersVector);
void sortDescending(vector<int> &numbersVector);
void printNumbers(vector<int> &numbersVector);





#endif /* !MYFUNCTIONS_H */

