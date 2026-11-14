
#include <iomanip>
#include <iostream>
#include <ostream>
bool vis[9];
int out[9];
void choose(int n, int lev) {
    if (lev >= n) {
        for (int i = 0; i < n; i++) {
            std::cout << std::setw(5) << out[i];
        }
        std::cout << std::endl;
        return ;
    }

    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        vis[i] = true;
        out[lev] = i + 1;
        choose(n, lev + 1);
        vis[i] = false;
    }
}

int main() {
    int n;
    std::cin >> n;

    choose(n, 0);
}
