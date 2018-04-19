#include "graphmaker.hpp"

using namespace std;

vector<vector<int> > neighborlist_from_adjmatrix(const vector<vector<bool> >& adjmatrix){
    int n = adjmatrix.size();
    vector<vector<int> > res(adjmatrix.size());
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (adjmatrix [i][j]) {
        res [i].push_back(j);
    }
    return res;
}

void save_graph(const vector<vector<int> >& edges, const string name){
    ofstream fout (name + ".gvz", ofstream::out);
    fout << "strict graph " << name << " {\n";
    for(int i = 0; i < (int) edges.size(); i++) {
        for (auto e : edges [i]) if (e > i) fout << i << " -- " << e << ";\n";
    }
    fout << "}\n";
    fout.close();   
}

void save_graph(const vector<vector<bool> >& adjmatrix, const string name){
    save_graph(neighborlist_from_adjmatrix(adjmatrix), name);
}

