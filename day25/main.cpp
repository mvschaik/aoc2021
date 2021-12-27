#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void print_field(const std::vector<std::string>& field) {
  for (const auto& line : field) {
    std::cout << line << '\n';
  }
  std::cout << '\n';
}

int main(int c, char* argv[]) {
  std::ifstream file{argv[1]};
  std::string line;
  std::vector<std::string> field;
  while (std::getline(file, line)) field.push_back(line);

  int nrows = field.size();
  int ncols = field[0].size();

  std::vector<std::string> new_field = field;
  for (int i = 0;; i++) {
    bool moved = false;
    // East
    for (int r = 0; r < nrows; r++) {
      for (int c = 0; c < ncols; c++) {
        if (field[r][c] == '>' && field[r][(c+1)%ncols] == '.') {
          moved = true;
          new_field[r][c] = '.';
          new_field[r][(c+1)%ncols] = '>';
        }
      }
    }
    field = new_field;

    // South
    for (int c = 0; c < ncols; c++) {
      for (int r = 0; r < nrows; r++) {
        if (field[r][c] == 'v' && field[(r+1)%nrows][c] == '.') {
          moved = true;
          new_field[r][c] = '.';
          new_field[(r+1)%nrows][c] = 'v';
        }
      }
    }
    field = new_field;

    if (!moved) {
      std::cout << "Done in " << i+1 << " steps\n";
      break;
    }
  }
}

