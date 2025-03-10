#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> g(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            g[i][j] = c == '1';
        }
    }
    vector<vector<int>> id(n, vector<int>(m));
    int last_id = 0;
    int dx[] = {-1, -1, 0, 1, 1, 0};
    int dy[] = {-1, 0, 1, 0, -1, -1};
    auto safe = [&](int x, int y) { return x >= 0 && x < n && y >= 0 && y < m; };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (id[i][j])
                continue;
            if (!g[i][j])
                continue;
            id[i][j] = ++last_id;
            queue<array<int, 2>> q;
            q.push({i, j});
            while (q.size()) {
                auto [x, y] = q.front();
                q.pop();
                for (int d = 0; d < 6; d++) {
                    int nx = x + dx[d], ny = y + dy[d] + (dx[d] && !(x % 2));
                    if (!safe(nx, ny) || id[nx][ny] || !g[nx][ny])
                        continue;
                    id[nx][ny] = id[x][y];
                    q.push({nx, ny});
                }
            }
        }
    }
    int last_filled_id = last_id;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (id[i][j])
                continue;
            if (g[i][j])
                continue;
            id[i][j] = ++last_id;
            queue<array<int, 2>> q;
            q.push({i, j});
            while (q.size()) {
                auto [x, y] = q.front();
                q.pop();
                for (int d = 0; d < 6; d++) {
                    int nx = x + dx[d], ny = y + dy[d] + (dx[d] && !(x % 2));
                    if (!safe(nx, ny) || id[nx][ny] || g[nx][ny])
                        continue;
                    id[nx][ny] = id[x][y];
                    q.push({nx, ny});
                }
            }
        }
    }

    unordered_set<int> graph[last_id + 1];
    vector<int> dist(last_id + 1, 1e9);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int d = 0; d < 6; d++) {
                int nx = i + dx[d], ny = j + dy[d] + (dx[d] && !(i % 2));
                if (!safe(nx, ny) || g[nx][ny] == g[i][j])
                    continue;
                graph[id[i][j]].insert(id[nx][ny]);
                graph[id[nx][ny]].insert(id[i][j]);
            }
        }
    }
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    int start_from = -1;
    while (q.size()) {
        int cur = q.front();
        q.pop();
        start_from = cur;
        for (int nxt : graph[cur]) {
            if (dist[nxt] <= dist[cur] + 1)
                continue;
            dist[nxt] = dist[cur] + 1;
            q.push(nxt);
        }
    }
    dist.assign(last_id + 1, 1e9);
    q.push(start_from);
    dist[start_from] = 0;
    while (q.size()) {
        int cur = q.front();
        q.pop();
        for (int nxt : graph[cur]) {
            if (dist[nxt] <= dist[cur] + 1)
                continue;
            dist[nxt] = dist[cur] + 1;
            q.push(nxt);
        }
    }
    int diam = *max_element(dist.begin() + 1, dist.end()) + 1;
    int ans = diam / 2;
    if (diam % 2 && start_from > last_filled_id)
        ans++;
    cout << ans << "\n";
}