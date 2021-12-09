#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<std::string> sigs[2];

  while (true) {
    std::string s;
    std::cin >> s;
    if (!std::cin)
      break;
    sigs[0].push_back(s);
    sigs[1].push_back(s);
  }

  if (sigs[0].empty())
    throw std::runtime_error("[Error] Empty input");

  auto filter = [&] (int i, bool maj) {
    int cnt_on = 0, cnt_off = 0;
    for (const auto& sig: sigs[maj]) {
      if (sig[i] == '1')
        cnt_on++;
      else
        cnt_off++;
    }

    char remove;
    if (cnt_on == cnt_off)
      remove = maj ? '1' : '0';
    else if (cnt_on > cnt_off)
      remove = maj ? '1' : '0';
    else
      remove = maj ? '0' : '1';

    std::vector<std::string> n_sigs;
    for (const auto& sig: sigs[maj]) {
      if (sig[i] != remove)
        n_sigs.push_back(sig);
    }
    sigs[maj] = n_sigs;
  };

  auto get_dec = [&] (const std::string& num) -> int {
    int answer = 0;
    for (const auto& bit: num) {
      answer <<= 1;
      if (bit == '1')
        answer |= 1;
    }
    return answer;
  };


  for (int i = 0; (int) sigs[0].size() > 1; i++)
    filter(i, 0);

  for (int i = 0; (int) sigs[1].size() > 1; i++)
    filter(i, 1);

  if (sigs[0].empty())
    throw std::runtime_error("[Error] sigs[0] is empty");
  if (sigs[1].empty())
    throw std::runtime_error("[Error] sigs[1] is empty");

  int oxy = get_dec(sigs[1][0]);
  int scrub = get_dec(sigs[0][0]);

  std::cout << oxy * scrub << "\n";

  return 0;
}
