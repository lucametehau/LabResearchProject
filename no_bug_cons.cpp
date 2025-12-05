#include "gog.h"
#include "magog.h"
#include <iostream>
#include <set>
#include <cassert>

int main() {
    int n;
    std::cin >> n;
    Triangle m(n);
    std::map<Trapezoid, int> m_count, g_count;
    std::map<int, int> counts;

    int count = 0;
    count_magog_brute(1, 1, n, m, count, m_count);
    // std::cout << "#Magog triangles of size " << n << " : " << count << "\n";
    // for (auto &[_, c] : t_count)
    //     std::cout << c << " ", counts[c]++;
    // std::cout << "\n";
    // for (auto &[cc, c] : counts)
    //     std::cout << "(" << cc << ", " << c << ")\n";
    
    Triangle g(n);

    count = 0;
    counts.clear();
    count_gog_brute(1, 1, n, g, count, g_count);
    // std::cout << "#Gog triangles of size " << n << " : " << count << "\n";
    // for (auto &[_, c] : t_count)
    //     std::cout << c << " ", counts[c]++;
    // std::cout << "\n";
    // for (auto &[cc, c] : counts)
    //     std::cout << "(" << cc << ", " << c << ")\n";

    

    // Trapezoid gog_test3 = {
    //     {},
    //     {0, 3, 4, 5, 6, 6},
    //     {0, 2, 3, 3, 4, 5, 6},
    //     {0, 1, 2, 3, 4, 4, 4, 7},
    // };

    // std::cout << (g_count.find(gog_test3) != g_count.end()) << "\n";

    int cnt = 65777;

    // std::cout << m_count.size() << "\n";

    int cnt_dif = 0, cnt_total = 0;
    for (auto &[m, c] : m_count) {
        // m[1] is m[3]
        // m[3] is m[1]
        auto m1 = m[1], m2 = m[2], m3 = m[3];
        if (bug_magog(m3, m2) || bug_magog(m2, m1))
            continue;
        
        cnt_dif++;
        cnt_total += c;

        // if (c == 1) {
        //     show_magog(m);
        // }
    }

    std::cout << cnt_dif << " distinct bugless Magog trapezoids, " << cnt_total << " total bugless Magog trapezoids\n";

    // std::cout << g_count.size() << "\n";

    cnt_dif = 0, cnt_total = 0;
    for (auto &[g, c] : g_count) {
        // std::cout << "bbb\n";
        // auto g1 = g[1];
        // auto g2 = g[2];
        // g1.pop_back();
        // g2.pop_back();
        // if (bug_gog(g1, g2) || bug_gog(g[2], g[3])) continue;

        auto g1 = g[1], g2 = g[2], g3 = g[3];
        if (bug_gog(g1, g2) || bug_gog(g2, g3)) 
            continue;
        cnt_dif++;
        cnt_total += c;
    }

    std::cout << cnt_dif << " distinct bugless Gog trapezoids, " << cnt_total << " total bugless Gog trapezoids\n";
    return 0;

    // for (auto &[m, _] : m_count) {
    //     if (m[1][n - 2] < m[1][n - 1] && m[1][n - 1] < m[1][n]) {
    //         std::cout << m[2][n - 2] - m[2][n - 1] << "\n";
    //     }
    // }

    while (true) {
        int cnt;
        std::cin >> cnt;
        for (auto &[m, _] : m_count) {
            cnt--;
            if (cnt == 0) {
                show_magog(m);
                auto b = base_right(m);
                std::cout << "Trapezoids with same base:\n";
                for (auto &t : base_count[b])
                    show_magog(t);
                break;
            }
        }
    }

    Trapezoid magog_test = {
        {},
        {0, 1, 2, 2, 4, 4, 6, 7, 7},
        {0, 1, 1, 2, 4, 4, 6, 7}
    };

    Trapezoid gog_test = magog_to_gog2(magog_test);
    show_magog(magog_test);
    show_gog(gog_test);

    Trapezoid magog_test2 = {
        {},
        {0, 1, 2, 2, 4, 4, 6, 6, 8},
        {0, 1, 1, 2, 3, 4, 4, 5}
    };

    Trapezoid gog_test2 = magog_to_gog2(magog_test2);
    show_magog(magog_test2);
    show_gog(gog_test2);

    std::set<Trapezoid> dif;
    for (auto &[m, _] : m_count) {
        auto g = magog_to_gog2(m);
        assert(g_count.find(g) != g_count.end());
        if (dif.find(g) != dif.end()) {
            show_magog(m);
            show_gog(g);
            return 0;
        }
        dif.insert(g);
    }

    std::cout << m_count.size() << " " << dif.size() << " " << g_count.size() << "\n";
    return 0;
}