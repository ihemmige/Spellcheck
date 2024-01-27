#include "helper.h"
#include <iostream>

int main() {
    // load in the dictionary
    ifstream file = open_file("words.txt");
    unordered_set<string> dictionary;
    load_dictionary(dictionary, file);

    // query the user for words, and check if in dictionary/closest existent words
    while (1) {
      user_interaction(dictionary);
      cout << endl;
    }
    return 0;
}