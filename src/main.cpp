#include <iostream>
#include <thread>

#include "folly/system/MemoryMapping.h"

int main() {
  std::string path = u8"D:\\¾µÏñÎÄ¼þ\\ubuntu-22.04.4-desktop-amd64.iso";
  folly::File f(path);
  folly::MemoryMapping memMap(folly::File(f.fd()));
  auto range = memMap.range();
  for (auto c : range) {
    std::cout << c << std::endl;
  }
  std::cout << memMap.data().size() << std::endl;
  return 0;
}