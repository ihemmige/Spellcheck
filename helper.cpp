#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include "helper.h"

using namespace std;

struct CompareBySecond {
    // for a max heap
    bool operator()(const pair<string, int>& lhs, const pair<string, int>& rhs) const {
        return lhs.second < rhs.second;
    }
};

int lev_distance(string w1, string w2) {
  if (w2.size() == 0) return w1.size();
  if (w1.size() == 0) return w2.size();
  if (w1[0] == w2[0]) return lev_distance(w1.substr(1), w2.substr(1));

  int a = lev_distance(w1.substr(1), w2);
  int b = lev_distance(w1, w2.substr(1));
  int c = lev_distance(w1.substr(1), w2.substr(1));
  return min({a,b,c}) + 1;
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
    vector<vector<int> > dp(rows, vector<int>(columns));

    // initialize the top row and left column
    for (int i = 0; i < rows; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j < columns; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i < rows; i++) {
      for (int j = 1; j < columns; j++) {
        int a = dp[i-1][j] + 1;
        int b = dp[i][j-1] + 1;
        int c = (w1[i-1] == w2[j-1]) ? dp[i-1][j-1] : dp[i-1][j-1] + 1;
        dp[i][j] = min({a,b,c});
      }
    }
    return dp.back().back();
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
    priority_queue<pair<string, int>, vector<pair<string, int> >, CompareBySecond> maxHeap;
    for (auto dict_word : dictionary) {
        count += 1;
        maxHeap.push(make_pair(dict_word, lev_distance_dp(word, dict_word)));
        if (maxHeap.size() > 10) {
            maxHeap.pop();
        }
    }
    vector<pair<string, int> > result;
    for (int i = 0; i < 10; i++) {
        result.push_back(maxHeap.top());
        // result.insert(result.begin(), maxHeap.top());
        maxHeap.pop();
    }
    reverse(result.begin(), result.end());
    return result;
}

void print_matches(vector<pair<string, int> >& neighbors) {
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
      auto start = chrono::high_resolution_clock::now();
      vector<pair<string, int> > result = find_neighbors(input, dictionary);
      auto end = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
      cout << "Time taken: " << duration.count() << " microseconds" << endl;
      cout << "The word is not in the dictionary." << endl;
      cout << "Top matches: " << endl;
      print_matches(result);
  }
}