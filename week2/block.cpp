/*
C++ Review
2D Dynamic Array Example with User-defined Data Type
*/

#include <iostream>
using namespace std;

// Struct Block (x and y are the members of the Struct)
struct Block {
  size_t x = 0; size_t y = 0;
};

// Print a block with the members (x and y)
ostream& operator<<(ostream& out, Block block) {
  out << block.x << ":" << block.y;
  return out;
}

// Entry point of the program
int main() {
  size_t width = 0;
  size_t height = 0;
  cout << "Enter width and height: ";
  cin >> width >> height;

// Allocate a 2D dynamic array of blocks (Array of pointer to pointers)
  Block** grid = new Block*[height];
  for (size_t y = 0; y < height; ++y) {
    grid[y] = new Block[width];
  }


  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      grid[y][x].x = x + 1; // Assign the location pointed to by grid[y][x].x to x+1
      grid[y][x].y = y + 1; // Assign the location pointed to by grid[y][x].y to y+1
      cout << grid[y][x] << " ";
    }
    cout << endl;
  }

  // Deallocate the 2D grid of blocks
  for (size_t y = 0; y < height; ++y) {
    delete[] grid[y];
  }
  delete[] grid;
}
