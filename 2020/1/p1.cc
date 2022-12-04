#include <iostream>
#include <unordered_set>

int main() {
  int num = 0;
  std::unordered_set<int> nums;
  while (std::cin >> num) {
    nums.insert(num);
  }
  for (const int num1 : nums) {
    const int num2 = 2020 - num1;
    if (nums.count(num2) > 0) {
      std::cout << num1 << " " << num2 << " " << num1 * num2 <<std::endl;
      exit(0);
    }
  }
  std::cout << "None found!?!?" << std::endl;
}

