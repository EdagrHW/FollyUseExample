#include <fstream>
#include <iostream>

#include "folly/Random.h"
#include "folly/system/MemoryMapping.h"

namespace memory_mapping {
void writeStringToFileOrDie(const std::string& str, int fd) {
  const char* b = str.c_str();
  size_t count = str.size();
  ssize_t total_bytes = 0;
  ssize_t r;
  do {
    r = write(fd, b, count);
    if (r == -1) {
      if (errno == EINTR) {
        continue;
      }
    }

    total_bytes += r;
    b += r;
    count -= r;
  } while (r != 0 && count);
}

void MemoryMappingTest() {
  const size_t M_PAGE_SIZE = 64 * 1024;
  using namespace folly;
  std::string fileData;
  size_t fileSize = M_PAGE_SIZE * 3 + 10;
  fileData.reserve(fileSize);
  for (size_t i = 0; i < fileSize; i++) {
    fileData.push_back(0xff & Random::rand32());
  }

  File f = File::temporary();
  writeStringToFileOrDie(fileData, f.fd());

  {
    size_t size = M_PAGE_SIZE * 2;
    size_t offset = M_PAGE_SIZE;
    MemoryMapping m(File(f.fd()), offset, size - 9);
    std::cout << std::hex << (int)fileData[offset] << std::endl;
    std::cout << std::hex << (int)m.data()[0] << std::endl;
    assert(fileData[offset] == m.data()[0]);
  }
}
}  // namespace memory_mapping
