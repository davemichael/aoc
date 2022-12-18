#include <iostream>
#include <string>
#include <vector>

bool any_same(const std::vector<int>& counts) {
  for (auto iter = counts.begin(); iter != counts.end(); ++iter) {
    if (*iter > 1) return true;
  }
  return false;
}

size_t location(const std::string& s, size_t count) {
  std::vector<int> char_count(26);
  size_t i;
  for (i = 0; i < count; ++i) { ++char_count[s[i]-'a']; }

  for (i = count; any_same(char_count); ++i) {
    --char_count[s[i-count]-'a'];
    ++char_count[s[i]-'a'];
  }
  return i;
}

int main() {
  std::vector<std::string> inputs = {
    std::string("mjqjpqmgbljsphdztnvjfqwrcgsmlb"),
    std::string("bvwbjplbgvbhsrlpgdmjqwftvncz"),
    std::string("nppdvjthqldpwncqszvftbrmjlhg"),
    std::string("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"),
    std::string("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw")
  };
  inputs.push_back("");
  std::getline(std::cin, inputs.back());

  for (auto iter = inputs.begin(); iter != inputs.end(); ++iter) {
    std::cout << location(*iter, 4) << std::endl;
  }
  for (auto iter = inputs.begin(); iter != inputs.end(); ++iter) {
    std::cout << location(*iter, 14) << std::endl;
  }
}
