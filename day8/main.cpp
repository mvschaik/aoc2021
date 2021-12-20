#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <array>

int diff_size(const std::string& s1, const std::string& s2) {
  std::vector<char> difference;
  std::set_difference(s1.begin(), s1.end(),
                      s2.begin(), s2.end(),
                      std::back_inserter(difference));
  return difference.size();
}

int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};

  int total1 = 0;
  int total2 = 0;

  std::string input;
  while (file) {
    std::vector<std::string> inputs;
    std::array<std::string, 10> found;
    for (int i = 0; i < 10; i++) {
      file >> input;
      if (!file) break; // eof
      std::sort(input.begin(), input.end());
      inputs.push_back(input);
      if (input.size() == 2) found[1] = input;
      if (input.size() == 3) found[7] = input;
      if (input.size() == 4) found[4] = input;
      if (input.size() == 7) found[8] = input;
    }
    if (!file) break; // eof

    // 2nd pass
    for (const auto& input : inputs) {
      if (input.size() == 5 && diff_size(found[1], input) == 0) found[3] = input;
      if (input.size() == 6 && diff_size(found[4], input) == 0) found[9] = input;
    }
    // 3rd pass
    for (const auto& input : inputs) {
      if (input.size() == 5 && input != found[3] && diff_size(input, found[9]) == 0) found[5] = input;
      if (input.size() == 6 && input != found[9] && diff_size(found[1], input) != 0) found[6] = input;
    }
    // 4th pass....
    for (const auto& input : inputs) {
      if (input.size() == 5 && input != found[5] && input != found[3]) found[2] = input; 
      if (input.size() == 6 && input != found[6] && input != found[9]) found[0] = input;
    }

    std::unordered_map<std::string, int> mapping;
    for (int i = 0; i < found.size(); i++) {
      mapping.insert({found[i], i});
    }

    file >> input; if (input != "|") std::cerr << "Expected '|' but got " << input << '\n';

    int num = 0;
    for (int i = 0; i < 4; i++) {
      file >> input;
      sort(input.begin(), input.end());
      num *= 10;
      num += mapping[input];
      if (mapping[input] == 1 || mapping[input] == 4 || mapping[input] == 7 || mapping[input] == 8)
          total1++;
    }
    total2 += num;
  }
  std::cout << "Number of 1/4/7/8's: " << total1 << '\n';
  std::cout << "Sum: " << total2 << '\n';
}
