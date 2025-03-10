#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;

int n, k;
vector<int> g[N];

stack<int> stk;
bool in_stack[N], vis[N];
vector<int> cycle;
bool in_cycle[N];
bool find_cycle(int c, int p) {
    vis[c] = 1;
    stk.push(c);
    in_stack[c] = 1;
    bool seen_p = 0;
    for (int nxt : g[c]) {
        if (in_stack[nxt]) {
            if (nxt == p && !seen_p) {
                seen_p = 1;
                continue;
            }
            while (stk.top() != nxt) {
                cycle.push_back(stk.top());
                stk.pop();
            }
            cycle.push_back(stk.top());
            return true;
        }
        if (vis[nxt])
            continue;
        if (find_cycle(nxt, c))
            return true;
    }
    in_stack[c] = 0;
    stk.pop();
    return false;
}

int depth[N], p[N][20];
vector<int> paths_from_root;
void preprocess(int c, int pp) {
    depth[c] = depth[pp] + 1;
    if (depth[c] - 1 == paths_from_root.size())
        paths_from_root.push_back(0);
    paths_from_root[depth[c] - 1]++;
    p[c][0] = pp;
    for (int i = 1; i < 20; i++)
        p[c][i] = p[p[c][i - 1]][i - 1];
    for (int nxt : g[c]) {
        if (in_cycle[nxt] || nxt == pp)
            continue;
        preprocess(nxt, c);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    for (int i = 19; i >= 0; i--) {
        if (depth[p[u][i]] >= depth[v])
            u = p[u][i];
    }

    if (u == v)
        return u;

    for (int i = 19; i >= 0; i--) {
        if (p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];
    }

    return p[u][0];
}

int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }

int subtree_sz[N];
int current_cycle_root;
bool is_centroid[N];
void fill_subtree_sz(int c, int p) {
    subtree_sz[c] = 1;
    for (int nxt : g[c]) {
        if (nxt == p || (in_cycle[nxt] && nxt != current_cycle_root))
            continue;
        if (is_centroid[nxt])
            continue;
        fill_subtree_sz(nxt, c);
        subtree_sz[c] += subtree_sz[nxt];
    }
}

vector<int> centroid_tree[N];
int find_centroid(int c, int p, int total_size) {
    int centroid = c;
    for (int nxt : g[c]) {
        if (nxt == p || (in_cycle[nxt] && nxt != current_cycle_root) || is_centroid[nxt])
            continue;
        if (subtree_sz[nxt] > total_size / 2) {
            centroid = find_centroid(nxt, c, total_size);
        }
    }
    return centroid;
}

int construct_centroid(int c, int centr_p) {
    // cout << c << " " << centr_p << " " << subtree_sz[c] << " " << subtree_sz[centr_p] << endl;
    fill_subtree_sz(c, centr_p);
    int centroid = find_centroid(c, centr_p, subtree_sz[c]);
    is_centroid[centroid] = 1;
    for (int nxt : g[centroid]) {
        if (in_cycle[nxt] && nxt != current_cycle_root)
            continue;
        if (is_centroid[nxt])
            continue;
        int centroid_child = construct_centroid(nxt, centroid);
        centroid_tree[centroid].push_back(centroid_child);
    }
    return centroid;
}

ll ans;

vector<int> k_paths_centroid(int c) {
    vector<int> cur_subtree(1, c);
    unordered_map<int, int> cnt_paths;
    cnt_paths[0] = 1;
    for (int nxt : centroid_tree[c]) {
        auto child_subtree = k_paths_centroid(nxt);
        for (int ch : child_subtree) {
            int d = dist(c, ch);
            if (cnt_paths.count(k - d)) {
                ans += cnt_paths[k - d];
            }
            cur_subtree.push_back(ch);
        }
        for (int ch : child_subtree) {
            int d = dist(c, ch);
            cnt_paths[d]++;
        }
    }
    return cur_subtree;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    n = 2e5;
    k = 456;
    // cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int a, b;
        // cin >> a >> b;
        a = i + 1, b = i + 2;
        if (i == n - 1) {
            // a = 1, b = 2;
            b = 1;
        }
        g[a].push_back(b);
        g[b].push_back(a);
    }

    find_cycle(1, 0);

    for (int x : cycle) {
        // cout << x << "\n";
        in_cycle[x] = 1;
    }

    vector<vector<int>> paths_from_roots;
    for (int root : cycle) {
        current_cycle_root = root;
        paths_from_root.clear();
        preprocess(root, 0);
        int root_centroid = construct_centroid(root, 0);
        k_paths_centroid(root_centroid);
        paths_from_roots.push_back(paths_from_root);
        // for (auto &[length, cnt] : paths_from_root) {
        //     cout << length << " " << cnt << "\n";
        // }
    }

    deque<ll> dp;
    for (int i = 0; i < cycle.size(); i++) {
        // cout << i << "\n";
        // for (int x : dp)
        //     cout << x << " ";
        // cout << "\n";
        auto cur = paths_from_roots[i];
        for (int j = 0; j < cur.size() && j <= k; j++) {
            ans += dp.size() > k - j ? dp[k - j] * cur[j] : 0;
        }

        for (int j = 0; j < cur.size(); j++) {
            if (j >= dp.size())
                dp.push_back(0);
            dp[j] += cur[j];
        }
        dp.push_front(0);
        // cout << i << "\n";
        // for (int x : dp)
        //     cout << x << " ";
        // cout << "\n";
        // cout << ans << "\n";
    }

    // deque<ll> ndp;
    for (int i = 0; i + 1 < cycle.size(); i++) {
        auto cur = paths_from_roots[i];
        // for (int x : dp)
        //     cout << x << " ";
        // cout << "\n";
        for (int j = 0; j < cur.size(); j++) {
            dp[j + cycle.size()] -= cur[j];
        }
        // for (int x : dp)
        //     cout << x << " ";
        // cout << "\n";

        for (int j = 0; j < cur.size() && j <= k; j++) {
            ans += dp.size() > k - j ? dp[k - j] * cur[j] : 0;
            // ans += ndp.size() > k - j ? ndp[k - j] * cur[j] : 0;
        }

        // for (int j = 0; j < cur.size(); j++) {
        //     if (j >= dp.size())
        //         dp.push_back(0);
        //     dp[j] += cur[j];
        // }
        dp.push_front(0);
        // cout << ans << "\n";
    }

    cout << ans << "\n";
}