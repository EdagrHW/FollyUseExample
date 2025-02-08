#include <iostream>
#include <vector>

#include "folly/executors/CPUThreadPoolExecutor.h"
#include "folly/executors/IOThreadPoolExecutor.h"
#include "folly/futures/Future.h"

namespace thread_pool {
void CPUThreadPoolTest() {
  // ����һ���̳߳أ�����߳���Ϊ 4
  folly::CPUThreadPoolExecutor executor(4);

  // �ύ���񣬷���һ�� Future
  auto future1 = folly::via(&executor).thenValue([](auto&&) {
    std::cout << "task 1 at thread " << std::this_thread::get_id() << std::endl;
    return 42;
  });

  auto future2 = folly::via(&executor).thenValue([](auto&&) {
    std::cout << "task 2 at thread " << std::this_thread::get_id() << std::endl;
    return std::string("Hello from thread pool!");
  });

  // ��ȡ�����������ֱ��������ɣ�
  int result1 = std::move(future1).get();
  std::string result2 = std::move(future2).get();

  std::cout << "task 1 excute result: " << std::dec << result1 << std::endl;
  std::cout << "task 2 excute result: " << std::dec << result2 << std::endl;
}

void CollectTest() {
  folly::CPUThreadPoolExecutor executor(4);

  std::vector<folly::Future<int>> futures;

  for (int i = 0; i < 10; ++i) {
    futures.push_back(folly::via(&executor).thenValue([i](auto&&) {
      std::cout << "excute task " << i
                << " threadID: " << std::this_thread::get_id() << std::endl;
      return i * i;
    }));
  }

  // �ȴ������������
  auto results = folly::collect(futures).get();

  std::cout << "excute result: ";
  for (const auto& res : results) {
    std::cout << std::dec << res << " ";
  }
  std::cout << std::endl;
}

void IOThreadPoolTest() {
  const int numCores = std::thread::hardware_concurrency();
  constexpr int multiplier = 4;  // I/O �߳���������� CPU ������
  const int numThreads = numCores * multiplier;

  constexpr int numTasks = 20;  // ������ > �߳���

  std::cout << "CPU cores: " << numCores << ", using " << numThreads
            << " I/O threads.\n";

  auto executor = std::make_shared<folly::IOThreadPoolExecutor>(numThreads);

  // �ύ��� I/O ����
  std::vector<folly::Future<folly::Unit>> futures;
  for (int i = 0; i < numTasks; ++i) {
    futures.push_back(folly::via(executor.get(), [i] {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(100));  // ģ�� I/O ����
      std::cout << "Task " << i << " completed on thread "
                << std::this_thread::get_id() << "\n";
    }));
  }

  auto start = std::chrono::steady_clock::now();
  folly::collectAll(futures).get();  // �ȴ������������
  auto end = std::chrono::steady_clock::now();

  std::cout << "All tasks completed in "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << " ms.\n";

  executor->join();  // �ر��̳߳�
}
}  // namespace thread_pool
