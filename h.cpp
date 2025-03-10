#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n_primes(int n) {
    int ret = 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i)
            continue;
        if (n % (i * i) == 0)
            return 0;
        n /= i;
        ret++;
    }
    ret += n > 1;
    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    int a[n];
    for (int &x : a)
        cin >> x;
    ll ans = 0;
    for (ll i = 0; i < n; i++)
        ans += i * (i + 1) / 2;
    for (int d = 2; d <= 256; d++) {
        int p = n_primes(d);
        if (!p)
            continue;
        ll cur = 0, tot = 0, cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] % d)
                continue;
            cur += cnt * i - tot;
            tot += i;
            cnt++;
        }
        ans += p % 2 ? -cur : cur;
    }
    cout << ans << "\n";
}