#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <assert.h>

using namespace std::literals;

constexpr int kStrLen = 10 * 10000;

void time_calc(const std::function<void()>& func)
{
  auto start = std::chrono::high_resolution_clock::now();
  std::invoke(func);
  std::chrono::duration<double> d = std::chrono::high_resolution_clock::now() - start;
  std::cout << "took " << d.count() << "s\n";
}

int main()
{
  // 构造
  std::string_view str = "hello, string_view";

  // 迭代器
  for (auto it = str.begin(); it != str.end(); ++it) {
    std::cout << *it;
  }
  std::cout << '\n';

  // 元素访问
  std::cout << str.at(4) << '\n';
  std::cout << str.front() << '\n';
  std::cout << str.back() << '\n';
  std::cout << str.data() << '\n';

  // 容量
  std::cout << str.size() << ' ' << str.length() << ' ' << str.max_size() << '\n';
  std::cout << std::boolalpha << str.empty() << '\n';

  // 修改器
  str.remove_prefix(4);
  std::cout << str <<'\n';

  str = "hello, string_view";
  str.remove_suffix(8);
  std::cout << str << '\n';

  str = "hello, string_view";
  auto str2 = "hello, world"sv;
  str.swap(str2);
  std::cout << str << '\n' << str2 << '\n';

  // 操作
  str = "hello, string_view";
  char dest[12] = {0};
  std::size_t len = str.copy(dest, 11, 3);
  std::cout << dest << '\n';

  std::cout << str.substr(4, 8) << '\n';

  str2 = "hello, world"sv;
  std::cout << str.compare(str2) << '\n';

  std::cout << str.find("str", 0, 3) << '\n';

  std::cout << str.find('i') << ' ' << str.find_first_of('i') << '\n';
  std::cout << str.rfind('i') << ' ' << str.find_last_of('i') << '\n';

  std::cout << str.find_first_not_of('h') << '\n';

  // string string_view 效率对比
  time_calc([] {
    constexpr auto str = "hello, world!"sv;
    for (int i = 0; i < kStrLen; ++i) {
      constexpr auto sub = str.substr(3);
    }
  });

  time_calc([] {
    auto str = "hello, world!"s;
    for (int i = 0; i < kStrLen; ++i) {
      auto sub = str.substr(3);
    }
  });
  return 0;
}