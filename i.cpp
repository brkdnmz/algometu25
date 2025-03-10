#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 500;
    cin >> n;
    int cnt[n * n] = {};
    vector<array<short, 2>> locs[n * n];
    int grid[n][n];
    int id[n * n] = {};
    int last_id = 0;
    for (short i = 0; i < n; i++) {
        for (short j = 0; j < n; j++) {
            cin >> grid[i][j];
            cnt[--grid[i][j]]++;
            if (cnt[grid[i][j]] == n + 1) {
                id[grid[i][j]] = last_id++;
            }
            locs[grid[i][j]].push_back({i, j});
        }
    }
    ll ans = 0;
    for (int i = 0; i < n * n; i++) {
        if (cnt[i] <= n) {
            for (auto &[x, y] : locs[i]) {
                int mn = 1e9;
                for (auto &[ox, oy] : locs[i]) {
                    if (x == ox && y == oy)
                        continue;
                    mn = min(mn, abs(x - ox) + abs(y - oy));
                }
                if (mn == 1e9)
                    continue;
                ans += mn;
            }
        }
    }
    for (int cid = 0; cid < last_id; cid++) {
        vector<vector<short>> closest(n, vector<short>(n, 2 * n));
        vector<vector<short>> cur_ans(n, vector<short>(n, 2 * n));
        for (int i = 0; i < n; i++) {
            short cl = 2 * n;
            for (int j = 0; j < n; j++) {
                cur_ans[i][j] = cl;
                if (cnt[grid[i][j]] > n && id[grid[i][j]] == cid)
                    cl = 0;
                closest[i][j] = min(closest[i][j], cl++);
            }
            cl = 2 * n;
            for (int j = n - 1; j >= 0; j--) {
                cur_ans[i][j] = min(cur_ans[i][j], cl);
                if (cnt[grid[i][j]] > n && id[grid[i][j]] == cid)
                    cl = 0;
                closest[i][j] = min(closest[i][j], cl++);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (cnt[grid[i][j]] <= n || id[grid[i][j]] != cid)
                    continue;
                int mn = cur_ans[i][j];
                for (int ni = 0; ni < n; ni++) {
                    if (ni != i) {
                        mn = min(mn, abs(i - ni) + closest[ni][j]);
                    }
                }
                if (mn >= 2 * n)
                    continue;
                // cout << i << " " << j << " " << mn << "\n";
                ans += mn;
            }
        }
    }
    cout << ans << "\n";
}