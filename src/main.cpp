#include "MemoryMappingTest.h"
#include "ThreadPoolTest.h"
#include "EventBaseTest.h"

int main() {
  memory_mapping::MemoryMappingTest();
  thread_pool::CPUThreadPoolTest();
  thread_pool::IOThreadPoolTest();
  event_base_test::eventBaseTest();
  return 0;
}
