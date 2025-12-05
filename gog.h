#include "triangle.h"
#include <map>

void count_gog_brute(int i, int j, int n, Triangle& g, int& count, std::map<Trapezoid, int>& t_count) {
    if (i == n + 1) {
        count++;
        // std::cout << mat << "\n";
        t_count[g.left_trapezoid(K)]++;
        return;
    }
    
    if (j == i + 1) {
        count_gog_brute(i + 1, 1, n, g, count, t_count);
        return;
    }

    int l_bound = j == 1 ? 1 : std::max(g[i - 1][j - 1], g[i][j - 1] + 1);
    int r_bound = i == j ? n : g[i - 1][j];

    if (i == n) {
        if (l_bound <= j && j <= r_bound) {
            g[i][j] = j;
            count_gog_brute(i, j + 1, n, g, count, t_count);
            g[i][j] = 0;
        }
        return;
    }

    for (int val = l_bound; val <= r_bound; val++) {
        g[i][j] = val;
        count_gog_brute(i, j + 1, n, g, count, t_count);
        g[i][j] = 0;
    }
}