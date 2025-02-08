#include "MemoryMappingTest.h"
#include "ThreadPoolTest.h"

int main() {
  memory_mapping::MemoryMappingTest();
  thread_pool::CPUThreadPoolTest();
  thread_pool::IOThreadPoolTest();
  return 0;
}
