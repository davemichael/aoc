#include <map>
#include <iostream>
#include <string>

struct Range {
  int left = -1;
  int right = -1;
};
bool operator<(const Range& lhs, const Range& rhs) {
  if (lhs.left == rhs.left) return lhs.right < rhs.right;
  return lhs.left < rhs.right;
}

std::pair<Range, Range> ParseLine(const std::string& line) {
  const size_t comma = line.find_first_of(',');
  const size_t hyphen1 = line.find_first_of('-');
  const size_t hyphen2 = line.find_first_of('-', comma);
  // std::cout << line << std::endl;
  // example: 12-34,56-789
  int left1 = std::stoi(line.substr(0, hyphen1));
  int right1 = std::stoi(line.substr(hyphen1 + 1, comma));
  int left2 = std::stoi(line.substr(comma + 1, hyphen2));
  int right2 = std::stoi(line.substr(hyphen2 + 1, line.length()));
  // std::cout << left1 << " " << right1 << " "
  //           << left2 << " " << right2 << std::endl;
  return {{left1, right1}, {left2, right2}};
}

bool ShareAny(const Range& a, const Range& b) {
  return !(a.right < b.left || a.left > b.right);
}

int main() {
  std::string line;
  int sum = 0;
  while (std::getline(std::cin, line)) {
    auto elf_pair = ParseLine(line);
    if (ShareAny(elf_pair.first, elf_pair.second)) {
      ++sum;
    }
  }
  std::cout << sum << std::endl;
}

