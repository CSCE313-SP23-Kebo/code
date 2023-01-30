/*
Example: Fault after accessing a non-allocated memory page
 */


#include <iostream>
using namespace std;

int main() {

  //int numbers[5] = {7, 5, 6, 12, 35};
  int numbers[5]; // Reserve 5 * 4 Bytes of memory on Stack

  cout << "\nThe numbers are: ";

  //  Printing array elements
  for (int i = 0; i < 5; ++i) {
    cout << numbers[i] << "  ";
  }

  return 0;
}
