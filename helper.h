#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <fstream>
#include <unordered_set>

using namespace std;

int lev_distance(string w1, string w2);

void display_matrix(vector<vector<int> >& matrix);

int lev_distance_dp(string w1, string w2);

ifstream open_file(string filename);

void load_dictionary(unordered_set<string>& dictionary, ifstream& file);

void print_dictionary(unordered_set<string>& dictionary);

vector<pair<string, int> > find_neighbors(string word, unordered_set<string>& dictionary);

void print_matches(vector<pair<string, int> >& neighbors);

void user_interaction(unordered_set<string>& dictionary);

#endif