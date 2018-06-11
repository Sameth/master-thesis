#include"pp2p.hpp"

using std::min;

void count_recursive(vvi& blocks, int start, int marked, std::vector<bool>& disabled, std::vector<ll>& result) {
    if (start == (int)blocks.size()) {
        result [marked] ++;
        return;
    }
    if (!disabled [start]) {
        std::vector<int> newdis;
        for(int e : blocks [start]) if (!disabled [e]) {
            disabled [e] = true;
            newdis.push_back(e);
        }
        count_recursive(blocks, start + 1, marked + 1, disabled, result);
        for (int d : newdis) disabled [d] = false; 
    }
    count_recursive(blocks, start + 1, marked, disabled, result);
}

// Spocita 2-pakovania, rozdelene podla poctu vrcholov v 2-pakovani
std::vector<ll> count_2pack (vvi& edges) {
    // Zakladne prevody
    int n = edges.size();
    std::vector<bool> disabled(n, false);
    std::vector<ll> result(n, 0);
    vvi close_vertices(n);
    vvi dists(n, vi(n, 1023456789123456789LL));

    // Spocitame vzdialenost kazdej dvojice susedov, F-W.
    For(i, n) dists [i][i] = 0;
    For(i, n) for (int e : edges [i]) dists [i][e] = 1;
    For(k, n) For (i, n) For(j, n) dists [i][j] = min(dists [i][j], dists [i][k] + dists [k][j]);

    // Zapiseme zoznam vrcholov vo vzdialenosti <= 2
    For(i, n) For(j, n) if (dists [i][j] <= 2) close_vertices [i].push_back(j);


    count_recursive(close_vertices, 0, 0, disabled, result);
    while (result.back() == 0) result.pop_back();
    return result;
}

// Spocita pocet vlastnych parov. Graf zadany zoznamom susedov.
ll count_pp (vvi& edges) {
    std::vector<ll> packs = count_2pack(edges);
    ll n = edges.size();
    ll result = 0;
    For(i, packs.size()) result += packs [i] * (1LL << (n - i));
    return result;
}

