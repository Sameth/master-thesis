#include"pp2p.hpp"

bool error_done = false;

void count_recursive(vvi& blocks, int start, int marked, vector<bool>& disabled, vector<ll>& result) {
    if (start == (int)blocks.size()) {
        result [marked] ++;
        return;
    }
    if (!disabled [start]) {
        vector<int> newdis;
        for(int e : blocks [start]) if (!disabled [e]) {
            disabled [e] = true;
            newdis.push_back(e);
        }
        count_recursive(blocks, start + 1, marked + 1, disabled, result);
        for (int d : newdis) disabled [d] = false; 
    }
    count_recursive(blocks, start + 1, marked, disabled, result);
}

// Spocita 2-pakovania s prednastavenymi vrcholmi.
// preset [i] = -1, ak nie je urceny; 0 ak nesmie byt v 2-pakovani, 1 ak musi byt v 2-pakovani
// Rozdelene podla poctu vrcholov v 2-pakovani
vector<ll> count_2pack_lim (vvi& edges, vector<int>& preset) {
    // Zakladne prevody
    int n = edges.size();
    if (n != preset.size()) {
        cerr << "Nesedi pocet vrcholov a pocet prednastavenych vrcholov!\n";
        exit(1);
    }
    vector<bool> disabled(n, false);
    vector<ll> result(n, 0);
    vvi close_vertices(n);
    vvi dists(n, vi(n, 1023456789123456789LL));

    // Spocitame vzdialenost kazdej dvojice susedov, F-W.
    For(i, n) dists [i][i] = 0;
    For(i, n) for (int e : edges [i]) dists [i][e] = 1;
    For(k, n) For (i, n) For(j, n) dists [i][j] = min(dists [i][j], dists [i][k] + dists [k][j]);

    // Zapiseme zoznam vrcholov vo vzdialenosti <= 2
    For(i, n) For(j, n) if (dists [i][j] <= 2) close_vertices [i].push_back(j);

    // Prednastavime disabled: vypnute vrcholy budu disabled.
    // Pre zapnute vrcholy zakazeme ich okolie vzdialenosti 2 a zvysime
    // pocet vrcholov ktore su defaultne v 2-pakovani.
    int initiallymarked = 0;
    For(i, n) {
        if (preset [i] == 0) disabled [i] = true;
        if (preset [i] == 1) {
            disabled [i] = true;
            for(int e : close_vertices [i]) {
                disabled [e] = true;
                if (preset [e] == 1 && e != i) {
                    if (!error_done) {
                        cerr << "Dva prilis blizke vrcholy nastavene v 2-pakovani\n";
                        error_done = true;
                    }
                    return {0};
                }
            }
            initiallymarked ++;
        }
    }


    count_recursive(close_vertices, 0, initiallymarked, disabled, result);
    while (result.back() == 0) result.pop_back();
    return result;
}

// Spocita 2-pakovania. Rozelene podla poctu vrcholov v 2-pakovani.
// Graf je zadany zoznamom susedov.
vector<ll> count_2pack (vvi& edges) {
    vector<int> preset(edges.size(), -1);
    return count_2pack_lim(edges, preset);
}

// Spocita pocet vlastnych parov, niektore vrcholy maju nastavene, ci patria do 2-pakovania.
// preset [i] = -1, ak nie je urceny, 0 ak nema patrit a 1 ak ma patrit do 2-pakovania.
// Graf zadany zoznamom susedov.
ll count_pp_lim (vvi& edges, vector<int>& preset) {
    vector<ll> packs = count_2pack_lim(edges, preset);
    ll n = edges.size();
    ll result = 0;
    For(i, packs.size()) result += packs [i] * (1LL << (n - i));
    return result;
}

// Spocita pocet vlastnych parov. Graf zadany zoznamom susedov.
ll count_pp(vvi& edges) {
    vector<int> preset(edges.size(), -1);
    return count_pp_lim(edges, preset);
}
