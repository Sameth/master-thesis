#ifndef __PP2P_HPP_I
#define __PP2P_HPP_I
#include<bits/stdc++.h>

using namespace std;

#define mp(x,y) make_pair(x, y)
#define For(i, n) for (int i = 0; i < (int) n; i++)

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

void count_recursive(vvi& edges, int start, int marked, vector<bool>& disabled, vector<ll>& result);
vector<ll> count_2pack (vvi& edges);
ll count_pp (vvi& edges);
#endif
