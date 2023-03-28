/*
Example: Producer-Consumer with Condition Variable. Busy-wait implementation
*/

#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

std::mutex g_mutex;
bool g_ready = false;
int g_data = 0;

int produceData() {
  // Generate a random number
  int randomNumber = rand() % 1000;
  std::cout << "produce data: " << randomNumber << "\n";
  return randomNumber;
}

void consumeData(int data) { std::cout << "receive data: " << data << "\n"; }

// consumer thread function
void consumer() {
  while (true) {
    // While g_ready is false, wait ...
    while (!g_ready) {
      // sleep for 1 second
      std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    // Lock the mutex
    std::unique_lock<std::mutex> ul(g_mutex);
    consumeData(g_data);
    g_ready = false;
  }
}

// producer thread function
void producer() {
  while (true) {
    std::unique_lock<std::mutex> ul(g_mutex);
    // Produce the data
    g_data = produceData();
    g_ready = true;
    ul.unlock();
    while (g_ready) {
      // sleep for 1 second
      std::this_thread::sleep_for (std::chrono::seconds(1));
    }
  }
}

void consumerThread() { consumer(); }

void producerThread() { producer(); }

int main() {
  std::thread t1(consumerThread);
  std::thread t2(producerThread);
  t1.join();
  t2.join();
  return 0;
}