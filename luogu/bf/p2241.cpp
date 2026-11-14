#include <iostream>
using ll = long long;
ll sq1;
ll sq2;
void solve(int h, int w) {
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (i == j) {
                sq1 += ((h - i) + 1) * ((w - j) + 1);
            }
            else {
                sq2 += ((h - i) + 1) * ((w - j) + 1);
            }

        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    solve(n, m);
    std::cout << sq1 << " " << sq2;
}
