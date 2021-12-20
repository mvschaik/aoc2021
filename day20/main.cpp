#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

typedef std::map<std::pair<int,int>,bool> Image;

template<typename K, typename V>
V get_or_default(const std::map<K,V>& map, const K& key, const V& deflt) {
  auto it = map.find(key);
  return it == map.end() ? deflt : it->second;
}

bool decode(Image& image, int row, int col, std::vector<bool> codex, bool edge) {
  int index;
  index   = 0; index |= (get_or_default(image, {row-1, col-1}, edge) ? 1 : 0);
  index <<= 1; index |= (get_or_default(image, {row-1, col  }, edge) ? 1 : 0);
  index <<= 1; index |= (get_or_default(image, {row-1, col+1}, edge) ? 1 : 0);
  index <<= 1; index |= (get_or_default(image, {row  , col-1}, edge) ? 1 : 0);
  index <<= 1; index |= (get_or_default(image, {row  , col  }, edge) ? 1 : 0);
  index <<= 1; index |= (get_or_default(image, {row  , col+1}, edge) ? 1 : 0);
  index <<= 1; index |= (get_or_default(image, {row+1, col-1}, edge) ? 1 : 0);
  index <<= 1; index |= (get_or_default(image, {row+1, col  }, edge) ? 1 : 0);
  index <<= 1; index |= (get_or_default(image, {row+1, col+1}, edge) ? 1 : 0);
  return codex[index];
}

void display(Image& image) {
  int min_row = 0;
  int min_col = 0;
  int max_row = 0;
  int max_col = 0;
  for (const auto& [c, p] : image) {
    min_row = std::min(min_row, c.first);
    max_row = std::max(max_row, c.first);
    min_col = std::min(min_col, c.second);
    max_col = std::max(max_col, c.second);
  }

  for (int row = min_row; row < max_row+1; row++) {
    for (int col = min_col; col < max_col+1; col++) {
      std::cout << (image[{row,col}] ? '#':'.');
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

int main(int argc, char* argv[]) {
  std::ifstream file {argv[1]};
  std::string line;
  std::vector<bool> codex;
  while (std::getline(file, line)) {
    if (line == "") break;
    for (char c : line) codex.push_back(c == '#');
  }

  std::map<std::pair<int,int>,bool> image;
  int row = 0;
  while (std::getline(file, line)) {
    for (int col = 0; col < line.size(); col++) {
      image[{row,col}] = line[col] == '#';
    }
    row++;
  }
  int min_row = 0;
  int max_row = row;
  int min_col = 0;
  int max_col = line.size();
  bool edge = codex[0];

  // display(image);

  for (int i = 0; i < 50; i++) {
    min_row-=2;
    max_row+=2;
    min_col-=2;
    max_col+=2;
    if (codex[0]) edge = !edge;
    std::map<std::pair<int,int>,bool> new_image;
    for (int row = min_row; row < max_row; row++) {
      for (int col = min_col; col < max_col; col++) {
        new_image[{row,col}] = decode(image, row, col, codex, edge);
      }
    }
    image = new_image;

    // display(image);

    if (!codex[0] || edge) {
      int num_pixels = std::count_if(image.begin(), image.end(), [](auto& t){ return t.second; });
      std::cout << "Number of active pixels after " << i+1 << " enhancements: " << num_pixels << '\n';
    }
  }
}
