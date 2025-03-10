#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<array<int, 2>> g[N];
vector<bool> vis(N);
int n;

bool dfs(int cur, int limit) {
    vis[cur] = 1;
    if (cur == n)
        return true;
    for (auto &[nxt, w] : g[cur]) {
        if (vis[nxt] || (limit & w) != w)
            continue;
        if (dfs(nxt, limit))
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    int ans = 0;
    for (int bit = 29; bit >= 0; bit--) {
        vis.assign(N, 0);
        if (dfs(1, ans + (1 << bit) - 1))
            continue;
        ans += 1 << bit;
    }
    cout << ans << "\n";
}