#include "graphmaker.hpp"
#include <bits/stdc++.h>

using namespace std;

#define For(i,n) for(int i = 0; i < n; i++)

int main () {
    int n, m;
    string name;
    cin >> n >> m >> name;
    vector<vector<int> > edglist(n);
    For(i, m) {
        int x, y;
        cin >> x >> y;
        edglist [x].push_back(y);
        edglist [y].push_back(x);
    }
    save_graph(edglist, name);
}
