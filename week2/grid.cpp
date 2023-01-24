/*
C++ Review
2D Dynamic Array Example with Built-in Data Type
*/


#include <iostream>
using namespace std;

int main() {
  size_t width = 0;
  size_t height = 0;
  cout << "Enter width and height: ";
  cin >> width >> height;

  int** grid = new int*[height];
  for (size_t y = 0; y < height; ++y) {
    grid[y] = new int[width];
  }

  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      grid[y][x] = (x + 1) + (width * y);
    }
  }

  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      cout << grid[y][x] << " ";
    }
    cout << endl;
  }

  for (size_t y = 0; y < height; ++y) {
    delete[] grid[y];
  }
  delete[] grid;
}
