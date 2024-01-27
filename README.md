# Spellcheck
Simple implementation of spell checking (brute force Levenshtein distance and Wagner-Fischer dynamic programming) as a method for misspelled word suggestion. Uses a text file with 1000 words as the "dictionary" of existing words. User can enter words, and if the word is not in the dictionary, the 10 closest matches based on Levenshtein distance are provided (word and distance provided).