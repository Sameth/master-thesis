#include"pp2p.hpp"

int n;
vector<vector<bool> > adjmatrix;
ll cyclepp;

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



void generate(int next, int maxcycle) {
    // Koncova podmienka
    if (next == n) {
        // Grafy, ktore nie su minimalne 2-hranovo suvisle, nema zmysel kontrolovat
        if (!minimallyconnected(next)) return;

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
        ll pp = count_pp(edges);

        // Ak sme nasli lepsie ako pre cyklus, chceme o tom vediet.
        if (pp > cyclepp) {
            cout << pp << endl;
            For(i, n) For(j, n) cout << adjmatrix [i][j] << endl;
            exit(0);
        }

        return;
    }


    // Zaciname od nicoho
    if (next == 0) {
        // Musime si zvolit velkost prveho cyklu
        for(int i = 3; i < n; i++) {
            // Nastavime cyklus
            For(j, i) {
                adjmatrix [j][(j+1)%i] = true;
                adjmatrix [(j+1)%i][j] = true;
            }

            generate(i, i);

            // Odstranime cyklus
            For(j, i) {
                adjmatrix [j][(j+1)%i] = false;
                adjmatrix [(j+1)%i][j] = false;
            }
        }
        return;
    }
    // Ak graf nie je minimalne 2-hranovo suvisly, uz nikdy nebude
    if (!minimallyconnected(next)) return;

    // Spocitame vzdialenost kazdej dvojice vrcholov doteraz
    vvi dists(next, vi(next, 1023456789123456789LL));
    For(i, next) For(j, next) if (adjmatrix [i][j]) dists [i][j] = 1;
    For(i, next) dists [i][i] = 0;
    For(k, next) For(i, next) For(j, next) dists [i][j] = min(dists [i][j], dists [i][k] + dists [k][j]);


    // Najprv vyskusame cykly do seba
    if (n - next > 1) {
        // Dlzka cyklu
        for (int i = 2; i <= min(n - next, maxcycle); i++) {
            // Spojime nove vrcholy v cykle
            For(j, i - 1) {
                adjmatrix [next + j][next + j + 1] = true;
                adjmatrix [next + j + 1][next + j] = true;
            }
            // Vrchol, kde pripojime cyklus
            For(j, next) {
                // Pripojime zaciatok a koniec
                adjmatrix [next][j] = true;
                adjmatrix [j][next] = true;
                adjmatrix [next + i - 1][j] = true;
                adjmatrix [j][next + i - 1] = true;

                // Rekurzivne volanie
                generate (next + i, maxcycle);

                // Odpojime zaciatok a koniec
                adjmatrix [next][j] = false;
                adjmatrix [j][next] = false;
                adjmatrix [next + i - 1][j] = false;
                adjmatrix [j][next + i - 1] = false;
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
        For(j, next) For(k, next) if (j != k && !adjmatrix [j][k]) {
            // Ak by sme pridanim ucha trivialne zvacsili maximalny cyklus,
            // koncime. Tuto moznost preskumame, ked zacneme vacsim cyklom.
            if (dists [j][k] + i > maxcycle) continue;

            // Spojime zaciatok a koniec ucha
            adjmatrix [j][next] = true;
            adjmatrix [next][j] = true;
            adjmatrix [k][next + i - 1] = true;
            adjmatrix [next + i - 1][k] = true;

            generate(next + i, maxcycle);

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

    cout << "Jednoduchy cyklus ma " << cyclepp << " pp\n";
    generate(0, -1);
    cout << "Mame " << grafov << " grafov.\n";
}
