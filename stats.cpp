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

    std::cout << "Magog " << K << "-trapezoid frequencies:\n";
    std::cout << "In total: " << m_count.size() << "\n";
    // for (auto &[_, c] : m_count)
    //     std::cout << c << " ";
    // std::cout << "\n";

    std::map<int, int> freq_of_freq;
    for (auto &[_, c] : m_count)
        freq_of_freq[c]++;
    for (auto &[x, c] : freq_of_freq)
        std::cout << "frequency " << x << " appears " << c << " times\n";
    std::cout << "\n";
    
    Triangle g(n);

    count = 0;
    counts.clear();
    count_gog_brute(1, 1, n, g, count, g_count);

    std::cout << "Gog " << K << "-trapezoid frequencies:\n";
    std::cout << "In total: " << g_count.size() << "\n";
    // for (auto &[_, c] : g_count)
    //     std::cout << c << " ";
    // std::cout << "\n";
    freq_of_freq.clear();
    for (auto &[_, c] : g_count)
        freq_of_freq[c]++;
    for (auto &[x, c] : freq_of_freq)
        std::cout << "frequency " << x << " appears " << c << " times\n";
    std::cout << "\n";
    
    return 0;
}