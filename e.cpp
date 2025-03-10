#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1000;

ll dist(ll x1, ll y1, ll x2, ll y2) { return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); }

int solve(int x, int y, ll tar) {
    int ans = 0;

    // top right
    int rx = (x + N - 1) / N * N, ry = (y + N - 1) / N * N;
    while (dist(x, y, rx, ry + N) <= tar)
        ry += N;
    for (;; rx += N) {
        while (ry >= (y + N - 1) / N * N && dist(x, y, rx, ry) > tar)
            ry -= N;
        if (ry < (y + N - 1) / N * N)
            break;
        ans += dist(x, y, rx, ry) == tar;
    }

    // top left
    rx = (x + N - 1) / N * N, ry = y / N * N;
    while (dist(x, y, rx, ry - N) <= tar)
        ry -= N;
    for (;; rx += N) {
        while (ry <= y / N * N && dist(x, y, rx, ry) > tar)
            ry += N;
        if (ry > y / N * N)
            break;
        ans += dist(x, y, rx, ry) == tar;
    }

    // bottom right
    rx = x / N * N, ry = (y + N - 1) / N * N;
    while (dist(x, y, rx, ry + N) <= tar)
        ry += N;
    for (;; rx -= N) {
        while (ry >= (y + N - 1) / N * N && dist(x, y, rx, ry) > tar)
            ry -= N;
        if (ry < (y + N - 1) / N * N)
            break;
        ans += dist(x, y, rx, ry) == tar;
    }

    // bottom left
    rx = x / N * N, ry = y / N * N;
    while (dist(x, y, rx, ry - N) <= tar)
        ry -= N;
    for (;; rx -= N) {
        while (ry <= y / N * N && dist(x, y, rx, ry) > tar)
            ry += N;
        if (ry > y / N * N)
            break;
        ans += dist(x, y, rx, ry) == tar;
    }

    if (y % N == 0) {
        rx = (x + N - 1) / N * N;
        while (dist(x, y, rx + N, y) <= tar)
            rx += N;
        ans -= dist(x, y, rx, y) == tar;

        rx = x / N * N;
        while (dist(x, y, rx - N, y) <= tar)
            rx -= N;
        ans -= dist(x, y, rx, y) == tar;
    }

    if (x % N == 0) {
        ry = (y + N - 1) / N * N;
        while (dist(x, y, x, ry + N) <= tar)
            ry += N;
        ans -= dist(x, y, x, ry) == tar;

        ry = y / N * N;
        while (dist(x, y, x, ry - N) <= tar)
            ry -= N;
        ans -= dist(x, y, x, ry) == tar;
    }

    return ans;
}

int solve2(int x, int y, ll tar) {
    int ans = 0;

    // top right
    int rx = (x + N - 1) / N * N, ry = (y + N - 1) / N * N;
    while (dist(x, y, rx, ry + N) <= tar)
        ry += N;
    for (;; rx += N) {
        while (ry >= (y + N - 1) / N && dist(x, y, rx, ry) > tar)
            ry -= N;
        if (ry < (y + N - 1) / N)
            break;
        ans += dist(x, y, rx, ry) == tar;
    }

    // top left
    rx = (x + N - 1) / N * N, ry = y / N * N;
    while (dist(x, y, rx, ry - N) <= tar)
        ry -= N;
    for (;; rx += N) {
        while (ry <= y / N && dist(x, y, rx, ry) > tar)
            ry += N;
        if (ry > y / N)
            break;
        ans += dist(x, y, rx, ry) == tar;
    }

    // bottom right
    rx = x / N * N, ry = (y + N - 1) / N * N;
    while (dist(x, y, rx, ry + N) <= tar)
        ry += N;
    for (;; rx -= N) {
        while (ry >= (y + N - 1) / N && dist(x, y, rx, ry) > tar)
            ry -= N;
        if (ry < (y + N - 1) / N)
            break;
        ans += dist(x, y, rx, ry) == tar;
    }

    // bottom left
    rx = x / N * N, ry = y / N * N;
    while (dist(x, y, rx, ry - N) <= tar)
        ry -= N;
    for (;; rx -= N) {
        while (ry <= y / N && dist(x, y, rx, ry) > tar)
            ry += N;
        if (ry > y / N)
            break;
        ans += dist(x, y, rx, ry) == tar;
    }

    if (y % N == 0) {
        rx = (x + N - 1) / N * N;
        while (dist(x, y, rx + N, y) <= tar)
            rx += N;
        ans -= dist(x, y, rx, y) == tar;

        rx = x / N * N;
        while (dist(x, y, rx - N, y) <= tar)
            rx -= N;
        ans -= dist(x, y, rx, y) == tar;
    }

    if (x % N == 0) {
        ry = (y + N - 1) / N * N;
        while (dist(x, y, x, ry + N) <= tar)
            ry += N;
        ans -= dist(x, y, x, ry) == tar;

        ry = y / N * N;
        while (dist(x, y, x, ry - N) <= tar)
            ry -= N;
        ans -= dist(x, y, x, ry) == tar;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    // ll rr = 500000 / t;
    while (t--) {
        char c;
        ll r = 0;
        while (1) {
            cin >> c;
            if (c == '.')
                break;
            r *= 10;
            r += c - '0';
        }
        for (int i = 0; i < 3; i++) {
            cin >> c;
            r *= 10;
            r += c - '0';
        }
        if (r < 500) {
            cout << "1\n";
            continue;
        }
        // r = rr;
        r *= r;
        int ans = 0;
        for (int i = 0; i <= 10; i++) {
            for (int j = 0; j <= N; j++) {
                ans = max(ans, solve(i, j, r));
            }
        }
        cout << max(2, ans) << "\n";
    }
}