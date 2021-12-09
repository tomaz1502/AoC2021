#include <iostream>
#include <vector>
#include <cassert>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<std::string> sigs;

  while (true) {
    std::string s;
    std::cin >> s;
    if (!std::cin)
      break;
    sigs.push_back(s);
  }

  assert(!sigs.empty() && "empty input");
  const int B = sigs[0].size();

  std::vector bits(B, 0);

  int gamma = 0, epsilon = 0;

  for (int i = 0; i < B; i++) {
    int cnt_g = 0;
    for (const auto& sig: sigs) {
      if (sig[i] == '1')
        cnt_g++;
      else
        cnt_g--;
    }
    if (cnt_g > 0)
      gamma |= (1 << (B - i - 1));
    else if (cnt_g < 0)
      epsilon |= (1 << (B - i - 1));
    else
      assert(false && "same number of bits on and off");
  }

  std::cout << gamma * epsilon << "\n";

  return 0;
}
