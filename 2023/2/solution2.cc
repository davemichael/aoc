#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using Counts = std::unordered_map<std::string, int>;

template <class T>
void skip_space(T& stream) {
  while (stream.peek() == ' ') { stream.get(); }
}

// E.g.:
// "3 blue, 4 red"
// -->
// {{"blue", 3}, {"red", 4}}
Counts GetCounts(const std::string& s) {
  Counts counts;
  std::istringstream istream(s);
  for (std::string line; std::getline(istream, line, ',');) {
    std::istringstream num_and_color(line);
    int num = 0;
    num_and_color >> num;
    skip_space(num_and_color);
    std::string color;
    num_and_color >> color;
    counts[color] = num;
  }
  return counts;
}

void GetMax(const Counts& input, Counts& max_counts) {
  for (const auto& [color, count] : input) {
    int& max_count = max_counts[color];
    max_count = std::max(count, max_count);
  }
}

Counts FindMaxes(const std::string& line) {
  std::istringstream linestream(line);
  std::string game_num;
  std::getline(linestream, game_num, ':');
  skip_space(linestream);
  Counts maxes;
  for (std::string draw; std::getline(linestream, draw, ';');) {
    GetMax(GetCounts(draw), maxes);
  }
  return maxes;
}

int main() {
  int sum = 0;
  for (std::string line; std::getline(std::cin, line);) {
    Counts m = FindMaxes(line);
    sum += m["red"] * m["blue"] * m["green"];
  }
  std::cout << sum << std::endl;
}
