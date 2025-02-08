#include <folly/MPMCQueue.h>
#include <folly/io/async/EventBase.h>

#include <fstream>
#include <future>
#include <iostream>
#include <vector>

namespace event_base_test {
using namespace folly;
namespace {
// ��ȡ�ļ����첽����
std::string readFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) return "Error opening file: " + filename;

  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  return content;
}
// ���� MPMCQueue������ EventBase �߳��д�����
void processNextFile(EventBase* evb,
                     MPMCQueue<std::pair<std::string, std::string>>& results) {
  evb->runInEventBaseThread([evb, &results] {
    std::pair<std::string, std::string> result;
    if (results.readIfNotEmpty(result)) {
      std::cout << "Read from " << result.first << ": "
                << result.second.substr(0, 100) << "...\n";

      // �������������е���һ������
      processNextFile(evb, results);
    } else {
      // �������Ϊ�գ��Ժ��ټ�飬���� busy-wait
      evb->runAfterDelay([evb, &results] { processNextFile(evb, results); },
                         10);  // ÿ 10ms ��ѯһ��
    }
  });
}
}  // namespace
void eventBaseTest() {
  EventBase eventBase;
  std::vector<std::future<std::string>> futures;
  MPMCQueue<std::pair<std::string, std::string>> results(100);  // �̰߳�ȫ����

  // 1. ���� 10 ���첽����
  for (int i = 1; i < 10; i++) {
    std::string filename =
        "C:\\Users\\28407\\Desktop\\test\\file" + std::to_string(i) + ".txt";

    futures.emplace_back(std::async(std::launch::async, [filename, &results] {
      std::string content = readFile(filename);
      results.blockingWrite(std::make_pair(filename, content));
      return content;
    }));
  }

  // 2. ���� MPMCQueue���첽�����ȡ������
  processNextFile(&eventBase, results);

  eventBase.loopForever();  // �����¼�ѭ��
}
}  // namespace event_base_test
