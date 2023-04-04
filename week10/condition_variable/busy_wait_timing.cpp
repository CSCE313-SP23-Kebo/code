/*
Example: Thread synchronization without condition variable. Busy-wait implementation
*/

#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
using namespace std;

std::mutex g_mutex;  // Locking mechanism
bool g_ready = false; // Notification

// Producer thread
void workThread() {
  std::cout << "Starting work thread ... \n";
  // Simulate work for 60 s
  std::this_thread::sleep_for(std::chrono::seconds(60));
  std::unique_lock<std::mutex> ul(g_mutex);  // acquire mutex
  g_ready = true;
  ul.unlock();
  // before exiting the function
}

// Consumer thread
void waitThread() {
  std::cout << "Inside wait thread ... \n";
  while(!g_ready){

  }
  //....
  std::cout << "Wait Thread Executed! \n";
}

int main() {
  std::thread t1(workThread);
  std::thread t2(waitThread);
  t1.join();
  t2.join();
  return 0;
}