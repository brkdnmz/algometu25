#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        int a[n];
        for (int &x : a)
            cin >> x;
        int ls[n], rs[n];
        stack<int> s;
        for (int i = 0; i < n; i++) {
            while (s.size() && a[s.top()] >= a[i])
                s.pop();
            ls[i] = s.size() ? s.top() : -1;
            s.push(i);
        }
        while (s.size())
            s.pop();
        for (int i = n - 1; i >= 0; i--) {
            while (s.size() && a[s.top()] >= a[i])
                s.pop();
            rs[i] = s.size() ? s.top() : -1;
            s.push(i);
        }
        while (q--) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int mid = (l + r) / 2;
            int cur = mid;
            ll ans = (ll)max(cur - l, r - cur) * a[cur];
            ans = min(ans, (ll)(r - l) * a[r]);
            ans = min(ans, (ll)(r - l) * a[l]);
            for (int it = 0; it < 500 && rs[cur] != -1 && rs[cur] <= r; it++) {
                cur = rs[cur];
                ans = min(ans, (ll)max(cur - l, r - cur) * a[cur]);
            }
            cur = mid - 1;
            if (cur >= l) {
                ans = min(ans, (ll)max(cur - l, r - cur) * a[cur]);
                for (int it = 0; it < 500 && ls[cur] != -1 && ls[cur] >= l; it++) {
                    cur = ls[cur];
                    ans = min(ans, (ll)max(cur - l, r - cur) * a[cur]);
                }
            }
            cout << ans << "\n";
        }
    }
}