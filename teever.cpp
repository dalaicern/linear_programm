#include <bits/stdc++.h>

#include "teever.hpp"

//#define int              long long
#define vi              vector<int >
#define vii              vector<vector<int > >
#define pii             pair<int , int >
#define R(i , n, a) for(int i = n; i >= a; i--)
#define all(x) begin(x), end(x)
#define debug(x) cout << #x << " = " << x << " "
#define debug2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << " "
#define debug3(x, y, z) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " "

using namespace std;
const int MOD = 1e9 + 7;

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;

    cout << "=> Bodoh bodlogonii toog oruulna uu: \n";
    cin >> t;
    for(int i = 1; i <= t; i++) {
        printf("\n\n=> %d. Shine bodlogo. \n\n", i);
        cout << "Achaa yvuulah gazriin too, Achaa huleen avah gazriin too\n";
        int n, m; cin >> n >> m;
        teever teever(n + 1, m + 1);
        
        teever.tulguur();
    }

}