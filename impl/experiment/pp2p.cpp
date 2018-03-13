#include"pp2p.hpp"

void count_recursive(vvi& edges, int start, int marked, vector<bool>& disabled, vector<ll>& result) {
    if (start == (int)edges.size()) {
        result [marked] ++;
        return;
    }
    if (!disabled [start]) {
        vector<int> newdis;
        queue<pii> todo;
        todo.push({start, 0});
        while(!todo.empty()) {
            auto top = todo.front();
            todo.pop();
            if (!disabled [top.first]) {
                newdis.push_back(top.first);
                disabled [top.first] = true;
            }
            if (top.second < 2) for (auto nei : edges [top.first]) todo.push(mp(nei, top.second + 1));
        }
        count_recursive(edges, start + 1, marked + 1, disabled, result);
        for (int d : newdis) disabled [d] = false; 
    }
    count_recursive(edges, start + 1, marked, disabled, result);
}

vector<ll> count_2pack (vvi& edges) {
    vector<bool> disabled(edges.size(), false);
    vector<ll> result(edges.size(), 0);
    count_recursive(edges, 0, 0, disabled, result);
    while (result.back() == 0) result.pop_back();
    return result;
}

ll count_pp (vvi& edges) {
    vector<ll> packs = count_2pack(edges);
    ll n = edges.size();
    ll result = 0;
    For(i, packs.size()) result += packs [i] * (1LL << (n - i));
    return result;
}

