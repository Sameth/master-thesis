#ifndef __PP2P_HPP_I
#define __PP2P_HPP_I
#include<bits/stdc++.h>

#define mp(x,y) std::make_pair(x, y)
#define For(i, n) for (int i = 0; i < (int) n; i++)

typedef long long ll;
typedef std::vector<ll> vi;
typedef std::vector<vi> vvi;
typedef std::pair<int, int> pii;

void count_recursive(vvi& edges, int start, int marked, std::vector<bool>& disabled, std::vector<ll>& result);
std::vector<ll> count_2pack (vvi& edges);
ll count_pp (vvi& edges);
#endif
