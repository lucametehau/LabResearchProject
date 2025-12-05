#include <iostream>
#include <vector>
#include <cassert>
#pragma once

const int K = 3;

using Trapezoid = std::vector<std::vector<int>>;

void show_magog(Trapezoid m) {
    int n = m[1].size() - 1;
    std::cout << "Magog\n";
    for (int j = 1; j < m.size(); j++) {
        for (int i = 1; i <= n - j + 1; i++) std::cout << m[j][i] << " ";
        std::cout << "\n";
    }
    std::cout << "------------\n";
}

void show_gog(Trapezoid g) {
    int n = g[1].size() - 1;
    std::cout << "Gog\n";
    for (int j = g.size() - 1; j >= 1; j--) {
        for (int i = 1; i <= n - j + 1; i++) std::cout << g[j][i] << " ";
        std::cout << "\n";
    }
    std::cout << "------------\n";
}

struct Triangle {
    std::vector<std::vector<int>> v;
    int n;

    Triangle() = default;
    Triangle(int n) : n(n) {
        v.resize(n + 1);
        for (int i = 1; i <= n; i++)
            v[i].resize(i + 1, 0);
    }

    std::vector<int>& operator [](int i) {
        return v[i];
    }

    Trapezoid right_trapezoid(int k) {
        Trapezoid t(k + 1);
        for (int i = 1; i <= k; i++) {
            t[i].push_back(0);
            for (int j = i; j <= n; j++)
                t[i].push_back(v[j][j - i + 1]);
        }
        return t;
    }

    Trapezoid left_trapezoid(int k) {
        Trapezoid t(k + 1);
        for (int i = 1; i <= k; i++) {
            t[i].push_back(0);
            for (int j = n; j >= i; j--)
                t[i].push_back(v[j][i]);
        }
        return t;
    }

    friend std::ostream& operator << (std::ostream& os, const Triangle& m) {
        int space_count = 0;
        for (int i = m.n; i >= 1; i--) {
            for (int j = 0; j < space_count; j++) {
                os << " ";
            }
            for (int j = 1; j <= i; j++) {
                os << m.v[i][j] << "   ";
            }
            os << "\n";
            space_count += 2;
        }
        os << "-----------------------";
        return os;
    }
};



std::vector<std::vector<int>> base_right(Trapezoid t) {
    return {};
    int n = t[1].size() - 1;
    int k = t.size() - 1;
    std::vector<std::vector<int>> base(k + 1);
    for (int i = 1; i <= k; i++) {
        base[i].resize(n - k + 1);
        for (int j = 1; j <= n - k + 1; j++)
            base[i][j] = t[i][j];
    }
    return base;
}

int bug_magog(const std::vector<int> &a, const std::vector<int> &b) {
    assert(a.size() + 1 == b.size());
    for (std::size_t i = 1; i + 3 <= b.size(); i++) {
        if (a[i + 1] > b[i] + 1)
            return i;
    }
    return 0;
}

int bug_gog(const std::vector<int> &a, const std::vector<int> &b) {
    assert(a.size() == b.size() + 1);
    int n = a.size() - 1;
    if (b[n - 2] <= a[n] + 1)
        return 0; // has bug, but it's the last thing, so don't consider it
    for (std::size_t i = n - 3; i >= 1; i--) {
        if (b[i] <= a[i + 2] + 1)
            return i;
    }
    return 0;
}

bool base_could_become_gog(
    const std::vector<int> &m3,
    const std::vector<int> &m2,
    const std::vector<int> &m1
) {

    int n = m1.size() - 2;
    for (int i = 1; i < n; i++) {
        if (m2[i+1] + 1 > m1[i] + 2) return false;
        if (m3[i+1] > m2[i] + 1) return false;
    }

    for (int i = 1; i <= n; i++) {
        if (m1[i] + 2 > i + 2) return false;
    }

    return true;
}

bool base_could_become_magog(
    const std::vector<int> &g1,
    const std::vector<int> &g2,
    const std::vector<int> &g3
) {

    int n = g3.size() - 1;

    for (int i = 1; i <= n; i++) {
        if (g3[i] - 2 > i) return false;
    }

    return true;
}

Trapezoid magog_to_gog2(Trapezoid m) {
    Trapezoid g(3);
    swap(m[1], m[2]);
    int n = m[2].size() - 1;

    g[1].resize(n + 1);
    g[2].resize(n);

    int i = bug_magog(m[1], m[2]);

    if (i) {
        // we have a bug
        if (m[1][i + 1] > m[2][i] + 1) {
            for (int j = 1; j < i; j++) g[2][j] = m[2][j] + 1;
            for (int j = i; j <= n - 1; j++) g[2][j] = m[2][j + 1];

            for (int j = 1; j <= i; j++) g[1][j] = m[1][j];
            g[1][i + 1] = m[2][i];
            for (int j = i + 2; j <= n; j++) g[1][j] = m[1][j - 1] - 2;

            return g;
        }
    }

    for (int i = 1; i <= n - 1; i++) g[1][i] = m[1][i];
    for (int i = 1; i <= n - 2; i++) g[2][i] = m[2][i] + 1;

    if (m[2][n - 1] < m[2][n]) {
        g[2][n - 1] = m[2][n];
        g[1][n] = m[2][n - 1];
    }
    else {
        g[2][n - 1] = m[2][n - 1] + 1;
        g[1][n] = m[2][n] + 1;
    }

    return g;
}

Trapezoid magog_to_gog3(Trapezoid m) {
    Trapezoid g(4);
    swap(m[1], m[2]);
    swap(m[2], m[3]);
    swap(m[3], m[1]);
    int n = m[3].size() - 1;

    g[1].resize(n + 1);
    g[2].resize(n);
    g[3].resize(n - 1);

    int i1 = bug_magog(m[1], m[2]), i2 = bug_magog(m[2], m[3]);

    // let's see if this is the bug definition for N x 3
    if (i1 || i2)
        return Trapezoid();

    // for (int i = 1; i <= n - 2; i++) {
    //     // we have a bug
    //     if (m[1][i + 1] > m[2][i] + 1) {
    //         for (int j = 1; j < i; j++) g[2][j] = m[2][j] + 1;
    //         for (int j = i; j <= n - 1; j++) g[2][j] = m[2][j + 1];

    //         for (int j = 1; j <= i; j++) g[1][j] = m[1][j];
    //         g[1][i + 1] = m[2][i];
    //         for (int j = i + 2; j <= n; j++) g[1][j] = m[1][j - 1] - 2;

    //         return g;
    //     }
    // }

    // no bugs somehow!

    for (int i = 1; i <= n - 3; i++) g[1][i] = m[1][i];
    for (int i = 1; i <= n - 3; i++) g[2][i] = m[2][i] + 1;
    for (int i = 1; i <= n - 3; i++) g[3][i] = m[3][i] + 2;

    if (m[2][n - 1] < m[2][n]) {
        g[2][n - 1] = m[2][n];
        g[1][n] = m[2][n - 1];
    }
    else {
        g[2][n - 1] = m[2][n - 1] + 1;
        g[1][n] = m[2][n] + 1;
    }

    return g;
}