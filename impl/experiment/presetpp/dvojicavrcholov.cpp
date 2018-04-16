#include<bits/stdc++.h>
#include"pp2p.hpp"

using namespace std;

int n;
vector<vector<bool> > adjmatrix;
ll cyclepp, bestother = -1;
ll najhorsiodhad = -1;

ll grafov = 0;

// Hlavna rekurzivna funkcia pre hladanie mostov. Vrati najmensie cislo
// vrchola po spatnej hrane. Ak objavi most, nastavi bridge na true.
ll dfs(int v, int pred, ll& num, vi& renumber, int actn, bool& bridge) {
    renumber [v] = num;
    ll minup = num;
    For(i, actn) if (i != pred && adjmatrix [v][i]) {
        if (renumber [i] == -1) {
            num ++;
            minup = min(dfs(i, v, num, renumber, actn, bridge), minup);
        }
        else {
            minup = min(minup, renumber [i]);
        }
    }
    if (v != 0 && minup == renumber [v]) bridge = true;
    return minup;
}

// Zisti, ci je graf aktualne ulozeny v adjmatrix minimalne 2-hranovo-suvisly
// Skusi odstranit kazdu hranu a hlada most.
bool minimallyconnected(int actn) {
    For(i, actn) For(j, actn) if (adjmatrix [i][j]) {
        // Sanity check
        if (i == j) {
            cerr << "Slucka v grafe!!!\n";
            exit(1);
        }
        // Cisovanie v dfs-strome
        vi renumber(actn, -1);
        // Odstranime hranu
        adjmatrix [i][j] = false;
        adjmatrix [j][i] = false;

        // Inicializacia poli a premennych
        ll num = 0;
        bool bridge = false;

        // Pocitanie
        dfs(0, -1, num, renumber, actn, bridge);

        // Vratime hranu
        adjmatrix [i][j] = true;
        adjmatrix [j][i] = true;

        // Ak nie je most, koncime.
        if (!bridge) {
            return false;
        }
    }
    return true;
}

int recursive_maxdist(int v, int t, ll mask, vvi& memo, int actn) {
    if (memo [v][mask] != -1) return memo [v][mask];
    if (v == t) return 0;

    int res = 0;
    For(i, actn) {
        if (adjmatrix [v][i] && (mask & (1 << i)) == 0) {
            res = max(res, 1 + recursive_maxdist(i, t, mask | (1<<i), memo, actn));
        }
    }
    memo [v][mask] = res;
    return res;
}

void compute_maxdists(vvi& result) {
    int actn = result.size();
    For(i, actn) {
        vvi memo(actn, vi(1<<actn, -1));
        For(j, actn) result [i][j] = recursive_maxdist(j, i, 1<<j, memo, actn);
    }
}


void generate(int next, int maxcycle, pii minadd) {
    // Koncova podmienka
    if (next == n) {
        // Grafy, ktore nie su minimalne 2-hranovo suvisle, nema zmysel kontrolovat
//        if (!minimallyconnected(next)) return;

        // Navysime pocitadlo grafov ;-)
        grafov ++;
        vvi edges(n);

        // Sanity check
        For(i, n) For(j, n) if (adjmatrix [i][j] != adjmatrix [j][i]) {
            cerr << "Nesymetricka matica susednosti!\n";
            exit(0);
        }

        // Zmenime reprezentaciu z matice susednosti na zoznam susedov
        For(i, n) For(j, n) if (adjmatrix [i][j]) edges[i].push_back(j);

        vector<int> preset(n, -1);

        // Pre kazdu dvojicu vrcholov a kazdu jej kombinaciu vypnutia/zapnutia
        // spocitame, kolko pp tak existuje.
        For(i, n) For(j, i) {
            ll ress[4];
            For(mode, 4) {
                preset [i] = mode & 1;
                preset [j] = mode >> 1;
                ress [mode] = count_pp_lim(edges, preset);
                preset [i] = -1;
                preset [j] = -1;
            }
            najhorsiodhad = max(najhorsiodhad, 3*ress[0] + 2*(ress [1] + ress [2] + ress[3]));
        }

        return;
    }


    // Zaciname od nicoho
    if (next == 0) {
        // Musime si zvolit velkost prveho cyklu
        for(int i = 3; i <= n; i++) {
            // Nastavime cyklus
            For(j, i) {
                adjmatrix [j][(j+1)%i] = true;
                adjmatrix [(j+1)%i][j] = true;
            }

            generate(i, i, minadd);

            // Odstranime cyklus
            For(j, i) {
                adjmatrix [j][(j+1)%i] = false;
                adjmatrix [(j+1)%i][j] = false;
            }
        }
        return;
    }

    // Ak graf nie je minimalne 2-hranovo suvisly, uz nikdy nebude
//    if (!minimallyconnected(next)) return;

    vvi dists(next, vi(next, -1));

    if (n - next > 0) compute_maxdists(dists);
    else {
        For(i, next) For(j, next) dists [i][j] = 1023456789LL;
        For(i, next) For(j, next) if (adjmatrix [i][j]) dists [i][j] = 1;
        For(i, next) dists [i][i] = 0;
        For(k, next) For(i, next) For(j, next) dists [i][j] = min(dists [i][j], dists [i][k] + dists [k][j]);
    }


    // Najprv vyskusame cykly do seba
    if (n - next > 1) {
        // Dlzka cyklu - pocet novych vrcholov
        for (int i = 2; i <= min(n - next, maxcycle - 1); i++) {
            // Spojime nove vrcholy v cykle
            For(j, i - 1) {
                adjmatrix [next + j][next + j + 1] = true;
                adjmatrix [next + j + 1][next + j] = true;
            }

            // Vrchol, kde pripojime cyklus
            For(j, next) {
                // Zakazeme pridanie na skorsiu dvojicu pozicii
                if (mp(j, j) >= minadd && (minadd != mp(-1, -1) || j == 0)) {
                    // Pripojime zaciatok a koniec
                    adjmatrix [next][j] = true;
                    adjmatrix [j][next] = true;
                    adjmatrix [next + i - 1][j] = true;
                    adjmatrix [j][next + i - 1] = true;

                    // Rekurzivne volanie
                    generate (next + i, maxcycle, {j,j});

                    // Odpojime zaciatok a koniec
                    adjmatrix [next][j] = false;
                    adjmatrix [j][next] = false;
                    adjmatrix [next + i - 1][j] = false;
                    adjmatrix [j][next + i - 1] = false;
                }
            }

            // Rozpojime nove vrcholy v cykle
            For(j, i - 1) {
                adjmatrix [next + j][next + j + 1] = false;
                adjmatrix [next + j + 1][next + j] = false;
            }
        }
    }

    // Vyskusame pridanie ucha
    // Cyklus cez dlzku ucha (pocet vrcholov)
    for (int i = 1; i <= n - next; i++) {
        // Spojime vrcholy v uchu
        For(j, i - 1) {
            adjmatrix [next + j][next + j + 1] = true;
            adjmatrix [next + j + 1][next + j] = true;
        }

        // Cykly cez konce ucha
        // Koniec nemoze byt ten isty a konce nemozu susedit (=> trivialne odstranitelna hrana)
        For(j, next) For(k, j) if (mp(j, k) >= minadd && !adjmatrix [j][k] && (minadd != mp(-1, -1) || k == 0)) {
            // Ak by sme pridanim ucha trivialne zvacsili maximalny cyklus,
            // koncime. Tuto moznost preskumame, ked zacneme vacsim cyklom.
            if (dists [j][k] + i + 1 > maxcycle) continue;

            // Spojime zaciatok a koniec ucha
            adjmatrix [j][next] = true;
            adjmatrix [next][j] = true;
            adjmatrix [k][next + i - 1] = true;
            adjmatrix [next + i - 1][k] = true;

            generate(next + i, maxcycle, {j, k});

            // Odpojime zaciatok a koniec ucha
            adjmatrix [j][next] = false;
            adjmatrix [next][j] = false;
            adjmatrix [k][next + i - 1] = false;
            adjmatrix [next + i - 1][k] = false;
        }


        // Rozpojime vrcholy v uchu
        For(j, i - 1) {
            adjmatrix [next + j][next + j + 1] = false;
            adjmatrix [next + j + 1][next + j] = false;
        }
        
    }
}


int main () {
    cin >> n;

    vvi edges(n);
    adjmatrix.resize(n, vector<bool>(n, false));

    For(i, n) {
        edges [i].push_back((i+1)%n);
        edges [(i+1)%n].push_back(i);
    }
    cyclepp = count_pp(edges);

    generate(0, -1, {-1,-1});
    cout << "Najhorsi odhad je " << najhorsiodhad << " s odmocninou " << pow(najhorsiodhad, 1.0/(n+1)) << endl;
}
