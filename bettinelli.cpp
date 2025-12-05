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