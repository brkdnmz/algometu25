#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int> &parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int m;
    cin >> n >> m;
    vector<int> g[n];
    capacity.resize(n);
    adj.resize(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        capacity[i].assign(n, 0);
        for (int nxt : g[i])
            capacity[i][nxt] = 1, adj[i].push_back(nxt);
    }
    if (g[0].size() == 1) {
        cout << "-1\n";
        return 0;
    }
    int ans = 1e9;
    for (int c : g[0]) {
        if (c == g[0][0])
            continue;

        for (int i = 0; i < n; i++) {
            capacity[i].assign(n, 0);
            for (int nxt : g[i])
                capacity[i][nxt] = 1, adj[i].push_back(nxt);
        }
        ans = min(ans, maxflow(g[0][0], c));
    }
    cout << ans - 1 << "\n";
}