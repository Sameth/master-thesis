#include"pp2p.hpp"

int n;
vector<vector<bool> > adjmatrix;
ll cyclepp;

ll grafov = 0;

void generate(int next) {
    // Koncova podmienka
    if (next == n) {
        grafov ++;
        vvi edges(n);
        For(i, n) For(j, n) if (adjmatrix [i][j] != adjmatrix [j][i]) {
            cerr << "Nesymetricka matica susednosti!\n";
            exit(0);
        }
        For(i, n) For(j, n) if (adjmatrix [i][j]) edges[i].push_back(j);
        ll pp = count_pp(edges);
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

            generate(i);

            // Odstranime cyklus
            For(j, i) {
                adjmatrix [j][(j+1)%i] = false;
                adjmatrix [(j+1)%i][j] = false;
            }
        }
        return;
    }
    // Najprv vyskusame cykly do seba
    if (n - next > 1) {
        // Dlzka cyklu
        for (int i = 2; i <= n - next; i++) {
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
                generate (next + i);

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
            // Spojime zaciatok a koniec ucha
            adjmatrix [j][next] = true;
            adjmatrix [next][j] = true;
            adjmatrix [k][next + i - 1] = true;
            adjmatrix [next + i - 1][k] = true;

            generate(next + i);

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
    generate(0);
    cout << "Mame " << grafov << " grafov.\n";
}
