#include"pp2p.hpp"

int main () {
    int n, m;
    cin >> n >> m;
    vvi edges(n);
    For(i, m) {
        int a, b;
        cin >> a >> b;
        edges [a].push_back(b);
        edges [b].push_back(a);
    }
    cout << "proper pairs: " << count_pp(edges) << endl;
    cout << "2-packings by chosen vertices:\n";
    vector<ll> packs = count_2pack(edges);
    For(i, packs.size()) cout << i << ": " << packs [i] << endl;
}
