#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    ll in[n + 1] = {}, out[n + 1] = {};
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        in[b] += c;
        out[a] += c;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans += max(0ll, out[i] - in[i]);
    cout << ans << "\n";
}