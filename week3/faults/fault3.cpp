#include <iostream>
using namespace std;

int main() {
  int* number;
  *number = 57;
  *(number + 2) = 6;
}
