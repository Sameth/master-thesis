#ifndef GRAPH_MAKER_H
#define GRAPH_MAKER_H

#include <bits/stdc++.h>
using namespace std;

vector<vector<int> > neighborlist_from_adjmatrix(const vector<vector<bool> >& adjmatrix);

void save_graph(const vector<vector<int> >& edges, string name);

void save_graph(const vector<vector<bool> >& adjmatrix, string name);

#endif
