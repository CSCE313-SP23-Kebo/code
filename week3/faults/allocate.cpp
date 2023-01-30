#include <iostream> 
#include <new>

int main () { 
  try
  { 
     int * myarray = new int[1000000000000]; 
  } 
  catch (std::bad_alloc & exception) 
  { 
     std::cerr << "bad_alloc detected: " << exception.what(); 
  } 
  return 0; 
} 