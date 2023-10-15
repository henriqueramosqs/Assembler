#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Usage: montador <filename>" << endl;
    exit(1);
  }

  filesystem::path filepath = argv[1];
  clog << "Filename: " << filepath.filename() << endl;

  ifstream fin(filepath);

  vector<string> words;

  string line;
  while (getline(fin, line)) {
    stringstream ss(line);
    string word;
    while (ss >> word) {
      if (!word.empty() && word.front() == ';') break;
      else words.push_back(word);
    }
  }

  std::clog << "Instructions: ";
  for (auto const& word : words) clog << word << ' ';
  clog << endl;
}
