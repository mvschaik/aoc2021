#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
  const int window_size = std::stoi(argv[1]);
  std::ifstream file{argv[2]};

  std::vector<int> measurements;
  int depth;
  while (file >> depth) {
    measurements.push_back(depth);
  }

  int increases = 0;
  int window = 0;
  for (int i = 0; i < measurements.size(); i++) {
    int previous = i < window_size ? INT32_MAX : window;
    window += measurements[i];
    if (i >= window_size) window -= measurements[i - window_size];

    if (window > previous) increases++;
  }

  std::cout << "There were " << increases << " increases\n";
}
