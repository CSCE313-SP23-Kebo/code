/*
C++ Review
2D Dynamic Array Example with Built-in Data Type (Integer)
*/


#include <iostream>
using namespace std;

int main() {
  size_t width = 0;
  size_t height = 0;
  cout << "Enter width and height: ";
  cin >> width >> height;

  // Create array (Pointer to pointer)
  int** grid = new int*[height];

 // Allocate memory for rows
  for (size_t y = 0; y < height; ++y) {
    grid[y] = new int[width];
  }

// Populate with numbers
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      grid[y][x] = (x + 1) + (width * y);
    }
  }

// Print content of data structure
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      cout << grid[y][x] << " ";
    }
    cout << endl;
  }
  
// Deallocate 
  for (size_t y = 0; y < height; ++y) {
    delete[] grid[y];
  }
  delete[] grid;
}
