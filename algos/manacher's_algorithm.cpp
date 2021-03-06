#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector <int> manacher(string &s) {
  int n = s.size();
  vector <int> maxp(n, 1);
  int c = 0, r = 0;
  for (int i = 1; i < n; i++) {
    if (2 * c - i >= 0) maxp[i] = min(r - i + 1, maxp[2 * c - i]);
    maxp[i] = max(maxp[i], 0);
    while (i + maxp[i] < n && i - maxp[i] >= 0 && s[i + maxp[i]] == s[i - maxp[i]]) maxp[i]++;
    if (i + maxp[i] - 1 > r) c = i, r = i + maxp[i] - 1;
  }
  return maxp;
}

int main() {
  string s;
  cin >> s;
  vector <int> maxp = manacher(s);
  for (int i = 0; i < (int)maxp.size(); i++)
    cout << maxp[i] << ' ';
  return 0;
}
