/*
C++ Review
2D Dynamic Array Example with Built-in Data Type (Integer)
*/

#include <iostream>
using namespace std;

int main()
{
  size_t width = 0;
  size_t height = 0;
  cout << "Enter width and height: ";
  cin >> width >> height;

  // Allocate a 2D array of pointers (Rows)
  int **grid = new int *[height];

  // Allocate data pointed to in each row (columns)
  for (size_t y = 0; y < height; ++y)
  {
    grid[y] = new int[width];
  }

  // Populate the grid with numbers
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      grid[y][x] = (x + 1) + (width * y);
    }
  }

  // Print
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      cout << grid[y][x] << " ";
    }
    cout << endl;
  }

  // Before deallocating the grid
   while (1)
    ;

  // Deallocate
  for (size_t y = 0; y < height; ++y)
  {
    delete[] grid[y];
  }
  delete[] grid;
}
