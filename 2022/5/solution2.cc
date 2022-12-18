#include <iostream>
#include <vector>
#include <string>

/*
                [V]     [C]     [M]
[V]     [J]     [N]     [H]     [V]
[R] [F] [N]     [W]     [Z]     [N]
[H] [R] [D]     [Q] [M] [L]     [B]
[B] [C] [H] [V] [R] [C] [G]     [R]
[G] [G] [F] [S] [D] [H] [B] [R] [S]
[D] [N] [S] [D] [H] [G] [J] [J] [G]
[W] [J] [L] [J] [S] [P] [F] [S] [L]
 1   2   3   4   5   6   7   8   9 
*/
std::vector<std::vector<char>> InitialState() {
  std::vector<std::vector<char>> stacks =
  {
    {'W', 'D', 'G', 'B', 'H', 'R', 'V'},
    {'J', 'N', 'G', 'C', 'R', 'F'},
    {'L', 'S', 'F', 'H', 'D', 'N', 'J'},
    {'J', 'D', 'S', 'V'},
    {'S', 'H', 'D', 'R', 'Q', 'W', 'N', 'V'},
    {'P', 'G', 'H', 'C', 'M'},
    {'F', 'J', 'B', 'G', 'L', 'Z', 'H', 'C'},
    {'S', 'J', 'R'},
    {'L', 'G', 'S', 'R', 'B', 'N', 'V', 'M'}
  };
  return stacks;
}

void PrintStacks(const std::vector<std::vector<char>>& stacks) {
  for (auto iter = stacks.begin(); iter != stacks.end(); ++iter) {
    for (auto jter = iter->begin(); jter != iter->end(); ++jter) {
      std::cout << *jter << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  auto stacks = InitialState();
  int count, src_loc, dest_loc;
  while (std::cin >> count >> src_loc >> dest_loc) {
    auto& src = stacks[src_loc-1];
    auto& dest = stacks[dest_loc-1];
    std::copy(src.begin() + src.size() - count, src.end(),
              std::back_inserter(dest));
    src.resize(src.size() - count);
    //std::cout << count << " " << src_loc << " " << dest_loc << std::endl;
    //PrintStacks(stacks);
  }
  for (int i = 0; i < 9; ++i) {
    std::cout << stacks[i].back();
  }
  std::cout << std::endl;
}

