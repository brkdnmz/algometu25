#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
const int bu_tolbiye_hakarettir = 1e9 + 7;

ll exp(ll a, ll b) {
    a %= bu_tolbiye_hakarettir;
    b %= bu_tolbiye_hakarettir - 1;
    ll r = 1;
    while (b) {
        if (b & 1)
            (r *= a) %= bu_tolbiye_hakarettir;
        (a *= a) %= bu_tolbiye_hakarettir;
        b >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, d;
    cin >> d >> n;
    vector<ll> forbidden[n];
    for (int i = 0; i < n; i++)
        forbidden[2 * i % n].push_back(i);

    ll ans = exp(n, d);
    ll div = exp(n, bu_tolbiye_hakarettir - 2);
    ll dmodn = d % n;
    for (int sum = 0; sum < n; sum++) {
        // cout << forbidden[sum].size() << "\n";
        // vector<ll> dp(n);
        // dp[0] = 1;
        // for (int dd = 0; dd < d; dd++) {
        //     vector<ll> ndp(n);
        //     for (int prev = 0; prev < n; prev++) {
        //         for (int cur = 0; cur < n; cur++) {
        //             if (forbidden[sum].count(cur))
        //                 continue;
        //             ndp[(prev + cur) % n] += dp[prev];
        //         }
        //     }
        //     dp.swap(ndp);
        //     for (int x : dp)
        //         cout << x << " ";
        //     cout << "\n";
        // }
        // cout << "\n";
        ll n_forbidden = forbidden[sum].size();
        ll tot = exp(n - n_forbidden, d);
        ll extra = exp(n_forbidden, d - 1);
        // tot += (d % 2 ? n_forbidden : n - n_forbidden) * exp(n_forbidden, d) % mod;
        // tot %= mod;
        bool special = (n_forbidden >= 1 && sum == forbidden[sum][0] * dmodn % n) ||
                       (n_forbidden == 2 && sum == (forbidden[sum][1] + forbidden[sum][0] * (dmodn + n - 1)) % n);
        ll sub = 0;
        if (special) {
            if (d % 2) {
                tot -= (n - n_forbidden) * extra % bu_tolbiye_hakarettir;
                tot += bu_tolbiye_hakarettir;
                tot %= bu_tolbiye_hakarettir;
            } else {
                tot += (n - n_forbidden) * extra % bu_tolbiye_hakarettir;
                tot += bu_tolbiye_hakarettir;
                tot %= bu_tolbiye_hakarettir;
            }
        } else {
            if (d % 2) {
                tot += n_forbidden * extra % bu_tolbiye_hakarettir;
                tot += bu_tolbiye_hakarettir;
                tot %= bu_tolbiye_hakarettir;
            } else {
                tot -= n_forbidden * extra % bu_tolbiye_hakarettir;
                tot += bu_tolbiye_hakarettir;
                tot %= bu_tolbiye_hakarettir;
            }
        }
        sub = tot * div % bu_tolbiye_hakarettir;
        ans += bu_tolbiye_hakarettir - sub;
        ans %= bu_tolbiye_hakarettir;
    }
    cout << ans << "\n";
}