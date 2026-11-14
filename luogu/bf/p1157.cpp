#include <iomanip>
#include <iostream>
#include <ostream>

int p[21];

void choose(int n, int r, int start, int lev) {
    if (lev >= r) {
        return ;
    }
    for (int i = start; i < n; i++) {
        p[lev] = i + 1;
        choose(n, r, i + 1, lev + 1);
        if (lev == r - 1) {
            for (int i = 0; i < r; i++) {
                std::cout << std::setw(3) << p[i];
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    int n, r;
    std::cin >> n >> r;
    choose(n, r, 0, 0);
}
