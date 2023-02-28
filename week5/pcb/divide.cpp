/*
Example: Divide by zero fault, not handled.
C++ program to illustrate, background process data
*/

#include <iostream>
using namespace std;

float divide(float numerator, float denominator)
{
	return (numerator / denominator);
}

int main()
{
	float numerator;
	float denominator;
	float quotient;

   //int *ptr  = new int[100];

  cout << "Enter the numerator: ";
  cin >> numerator;
  cout << "Enter the denominator: ";
  cin >> denominator;

	quotient = divide(numerator, denominator);
	cout << "The quotient is: " << quotient << endl;
}
