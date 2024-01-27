#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <utility>
#include "helper.h"

using namespace std;

int lev_distance(string w1, string w2) {
  if (w2.size() == 0) return w1.size();
  if (w1.size() == 0) return w2.size();
  if (w1[0] == w2[0]) return lev_distance(w1.substr(1), w2.substr(1));

  int a = lev_distance(w1.substr(1), w2);
  int b = lev_distance(w1, w2.substr(1));
  int c = lev_distance(w1.substr(1), w2.substr(1));
  return std::min({a,b,c}) + 1;
}

void display_matrix(vector<vector<int> >& matrix) {
    for (auto row : matrix) {
        for (auto col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

int lev_distance_dp(string w1, string w2) {
    int rows = w1.size() + 1;
    int columns = w2.size() + 1;
    std::vector<std::vector<int> > dp(rows, std::vector<int>(columns));

    // initialize the top row and left column
    for (int i = 0; i < rows; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j < columns; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i < rows; i++) {
      for (int j = 1; j < columns; j++) {
        int a = dp[i-1][j];
        int b = dp[i][j-1];
        int c = dp[i-1][j-1];
        if (w1[i-1] == w2[j-1]) {
          dp[i][j] = std::min({a,b,c});
        } else {
          dp[i][j] = std::min({a,b,c}) + 1;
        }
      }
    }
    return dp.back().back();

    // fill the dp table
    display_matrix(dp);
    return 0;
}

ifstream open_file(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening the file." << endl;
        exit(1); // Return an error code
    }
    return file;
}

void load_dictionary(unordered_set<string>& dictionary, ifstream& file) {
    string word;
    while (file >> word) {
        dictionary.insert(word);
    }
}

void print_dictionary(unordered_set<string>& dictionary) {
    for (auto word : dictionary) {
        cout << word << endl;
    }
}

vector<pair<string, int> > find_neighbors(string word, unordered_set<string>& dictionary) {
    vector<pair<string, int> > neighbors;
    int count = 0;
    for (auto dict_word : dictionary) {
        count += 1;
        int dist = lev_distance_dp(word, dict_word);
        neighbors.push_back(make_pair(dict_word, dist));
    }
    // sort the neighbors by distance
    sort(neighbors.begin(), neighbors.end(), [](auto& left, auto& right) {
        return left.second < right.second;
    });
    return vector<pair<string, int> >(neighbors.begin(), neighbors.begin() + 5);
}

void print_vector(vector<pair<string, int> >& neighbors) {
    for (auto neighbor : neighbors) {
        cout << neighbor.first << " " << neighbor.second << endl;
    }
}

void user_interaction(unordered_set<string>& dictionary) {
  string input;
  cout << "Enter a word: ";
  cin >> input;
  if (dictionary.count(input) != 0) {
    cout << "The word is in the dictionary." << endl;
  } else {
      cout << "The word is not in the dictionary." << endl;
      auto start = std::chrono::high_resolution_clock::now();
      vector<pair<string, int> > result = find_neighbors(input, dictionary);
      auto end = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
      cout << "Time taken: " << duration.count() << " microseconds" << endl;
      print_vector(result);
  }
}