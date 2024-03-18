#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Function to calculate LCS length
std::vector<int> lcs_length(const std::vector<std::string> &words_x,
                            const std::vector<std::string> &words_y) {
  std::vector<int> curr(words_y.size() + 1, 0);
  for (const auto &word_x : words_x) {
    std::vector<int> prev = curr;
    for (size_t y_i = 0; y_i < words_y.size(); ++y_i) {
      if (word_x == words_y[y_i]) {
        curr[y_i + 1] = prev[y_i] + 1;
      } else {
        curr[y_i + 1] = std::max(curr[y_i], prev[y_i + 1]);
      }
    }
  }
  return curr;
}

// Function for Hirschberg's algorithm
std::vector<std::string>
LCS_HIRSHBERG(const std::vector<std::string> &words_x,
              const std::vector<std::string> &words_y) {
  size_t len_x = words_x.size();
  if (len_x == 0) {
    std::vector<std::string> empty;
    return empty;
  } else if (len_x == 1) {
    if (std::find(words_y.begin(), words_y.end(), words_x[0]) !=
        words_y.end()) {
      std::vector<std::string> singleElement;
      singleElement.push_back(words_x[0]);
      return singleElement;
    } else {
      std::vector<std::string> empty;
      return empty;
    }
  } else {
    size_t i = len_x / 2;
    std::vector<std::string> x_beg(words_x.begin(), words_x.begin() + i);
    std::vector<std::string> x_end(words_x.begin() + i, words_x.end());
    std::vector<int> l1 = lcs_length(x_beg, words_y);
    std::vector<int> temp =
        lcs_length(std::vector<std::string>(x_end.rbegin(), x_end.rend()),
                   std::vector<std::string>(words_y.rbegin(), words_y.rend()));
    std::vector<int> l2(temp.rbegin(), temp.rend());

    std::vector<int> sum_l(l1.size());
    std::transform(l1.begin(), l1.end(), l2.begin(), sum_l.begin(),
                   std::plus<int>());

    size_t j = std::max_element(sum_l.begin(), sum_l.end()) - sum_l.begin();
    std::vector<std::string> y_beg(words_y.begin(), words_y.begin() + j);
    std::vector<std::string> y_end(words_y.begin() + j, words_y.end());

    auto left = LCS_HIRSHBERG(x_beg, y_beg);
    auto right = LCS_HIRSHBERG(x_end, y_end);
    left.insert(left.end(), right.begin(), right.end());
    return left;
  }
}

std::vector<std::string> readWords() {
  std::string line, word;
  std::vector<std::string> words;

  std::getline(std::cin, line);
  std::istringstream stream(line);

  while (stream >> word) {
    words.push_back(word);
  }

  return words;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  std::vector<std::string> X = readWords();
  std::vector<std::string> Y = readWords();

  auto start = std::chrono::high_resolution_clock::now();
  auto result = LCS_HIRSHBERG(X, Y);
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << result.size() << std::endl;

  if (result.size() > 0) {
    std::cout << result[0];
    for (size_t i = 1; i < result.size(); ++i) {
      std::cout << " " << result[i];
    }
    std::cout << std::endl;
  }

  // output in seconds
  std::cout << "TIME: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << " ms" << std::endl;
}
