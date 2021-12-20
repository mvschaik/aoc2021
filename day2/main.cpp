#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};
  int depth1 = 0;
  int depth2 = 0;
  int pos = 0;
  int aim = 0;

  std::string direction;
  int amount;
  while (file >> direction >> amount) {
    // Part 1
    if (direction == "up") depth1 -= amount;
    if (direction == "down") depth1 += amount;
    if (direction == "forward") pos += amount;

    // Part 2
    if (direction == "down") aim += amount;
    if (direction == "up") aim -= amount;
    if (direction == "forward") depth2 += amount * aim;
  }
  std::cout << "Part 1: depth: " << depth1 << ", position: " << pos;
  std::cout << ", multiplied: " << depth1 * pos << '\n';

  std::cout << "Part 2: depth: " << depth2 << ", position: " << pos;
  std::cout << ", multiplied: " << depth2 * pos << '\n';
}
