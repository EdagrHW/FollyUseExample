#include <folly/MPMCQueue.h>
#include <folly/io/async/EventBase.h>

#include <fstream>
#include <future>
#include <iostream>
#include <vector>

namespace event_base_test {
using namespace folly;
namespace {
// 读取文件的异步任务
std::string readFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) return "Error opening file: " + filename;

  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  return content;
}
// 监听 MPMCQueue，并在 EventBase 线程中处理结果
void processNextFile(EventBase* evb,
                     MPMCQueue<std::pair<std::string, std::string>>& results) {
  evb->runInEventBaseThread([evb, &results] {
    std::pair<std::string, std::string> result;
    if (results.readIfNotEmpty(result)) {
      std::cout << "Read from " << result.first << ": "
                << result.second.substr(0, 100) << "...\n";

      // 继续监听队列中的下一个数据
      processNextFile(evb, results);
    } else {
      // 如果队列为空，稍后再检查，避免 busy-wait
      evb->runAfterDelay([evb, &results] { processNextFile(evb, results); },
                         10);  // 每 10ms 轮询一次
    }
  });
}
}  // namespace
void eventBaseTest() {
  EventBase eventBase;
  std::vector<std::future<std::string>> futures;
  MPMCQueue<std::pair<std::string, std::string>> results(100);  // 线程安全队列

  // 1. 启动 10 个异步任务
  for (int i = 1; i < 10; i++) {
    std::string filename =
        "C:\\Users\\28407\\Desktop\\test\\file" + std::to_string(i) + ".txt";

    futures.emplace_back(std::async(std::launch::async, [filename, &results] {
      std::string content = readFile(filename);
      results.blockingWrite(std::make_pair(filename, content));
      return content;
    }));
  }

  // 2. 监听 MPMCQueue，异步处理读取的内容
  processNextFile(&eventBase, results);

  eventBase.loopForever();  // 运行事件循环
}
}  // namespace event_base_test
