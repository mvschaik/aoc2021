#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

// bitmask(3) == ...000111
int bitmask(int size) {
  int result = 0;
  while (size--) {
    result = (result<<1) | 1;
  }
  return result;
}

// bit_counts(ns)[i] >0 if more 1's than 0's @ bit i, <0 if less
// or 0 if equal num of 0s and 1s.
std::vector<int> bit_counts(const std::vector<std::string>& ns) {
  std::vector<int> counts;
  for (const auto& n : ns) {
    counts.resize(n.size());
    for (int i = 0; i < n.size(); i++) {
      counts[i] += (n[i] == '1') ? 1 : -1;
    }
  }
  return counts;
}

int most_common_bits(const std::vector<std::string>& ns) {
  auto counts = bit_counts(ns);
  int result = 0;
  for (int n : counts) {
    result = (result << 1) | (n > 0 ? 1 : 0);
  }
  return result;
}

std::string filter_by_bits(std::vector<std::string> numbers,
                           std::function<bool(bool bit, int count)> crit) {
  int n_bits = numbers[0].size();
  for (int i = 0; i < n_bits; i++) {
    int count = bit_counts(numbers)[i];
    numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [&](const auto& s) {
      return crit(s[i] == '1', count);
    }), numbers.end());
    if (numbers.size() == 1) {
      return numbers[0];
    }
  }
  std::cerr << "Ooops, don't know what to do with " << numbers.size() << " numbers left\n";
  exit(1);
}

int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};
  std::vector<std::string> numbers;
  std::string s;
  while (file >> s) {
    numbers.push_back(s);
  }
  int n_bits = numbers[0].size();

  int gamma = most_common_bits(numbers);
  int epsilon = (~gamma & bitmask(n_bits));
  std::cout << "Part 1: gamma: " << gamma << ", epsilon: " << epsilon << ", power: " << gamma * epsilon << '\n';

  int o2 = std::stoi(filter_by_bits(numbers, [](bool bit, int count){
    return (count >= 0) ^ bit;
  }), 0, 2);
  int co2 = std::stoi(filter_by_bits(numbers, [](bool bit, int count){
    return (count < 0) ^ bit;
  }), 0, 2);
  std::cout << "Part 2: o2: " << o2 << ", co2: " << co2 << ", rating: " << o2 * co2 << '\n';

}
