#include <iostream>
#include <vector>
#include <map>

inline std::map<std::vector<std::vector<int>>, std::vector<Trapezoid>> base_count;

void count_magog_brute(int i, int j, int n, Triangle& m, int& count, std::map<Trapezoid, int>& t_count) {
    // std::cout << i << " " << j << "\n";
    if (i == n + 1) {
        count++;
        // std::cout << mat << "\n";
        auto t = m.right_trapezoid(K);
        t_count[t]++;
        base_count[base_right(t)].push_back(t);
        return;
    }
    
    if (j == i + 1) {
        count_magog_brute(i + 1, 1, n, m, count, t_count);
        return;
    }

    int l_bound = j == 1 ? 1 : m[i - 1][j - 1];
    int r_bound = i == j ? i : m[i - 1][j];
    for (int val = l_bound; val <= r_bound; val++) {
        m[i][j] = val;
        count_magog_brute(i, j + 1, n, m, count, t_count);
        m[i][j] = 0;
    }
}