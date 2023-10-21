#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
using namespace std;

enum OPCODES {
  ADD = 1,
  SUB = 2,
  MUL = 3,
  DIV = 4,
  JMP = 5,
  JMPN = 6,
  JMPP = 7,
  JMPZ = 8,
  COPY = 9,
  LOAD = 10,
  STORE = 11,
  INPUT = 12,
  OUTPUT = 13,
  STOP = 14, };

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Usage: montador <filename>" << endl;
    exit(1);
  }

  filesystem::path filepath = argv[1];
  clog << "Filename: " << filepath.filename() << endl;

  ifstream fin(filepath);
  vector<int> mem;

  string line;
  while (getline(fin, line)) {
    stringstream ss(line);
    int val;
    while (ss >> val) mem.push_back(val);
  }

  clog << "Memory values: ";
  for (auto const& val : mem) clog << val << ' ';
  clog << endl;

  int PC = 0;
  int ACC = 0;

  cout << "PC <- " << PC << " ACC <- " << ACC << endl;

  auto check_pc = [&]() {
    if (PC >= size(mem)) {
      cout << "SEGMENTATION FAULT - Invalid PC Address " << PC << endl;
      exit(1);
    }
  };

  while (true) {

    check_pc();
    int inst = mem[PC++];
    if (inst == STOP) break;
    if (inst == COPY) {
      check_pc();
      int op1 = mem[PC++];
      check_pc();
      int op2 = mem[PC++];
      mem[op2] = mem[op1];
      continue;
    }

    check_pc();
  int op = mem[PC++];
    if (inst == ADD) ACC += mem[op];
    else if (inst == SUB) ACC -= mem[op];
    else if (inst == MUL) ACC *= mem[op];
    else if (inst == DIV) ACC /= mem[op];
    else if (inst == JMP) PC = op;
    else if (inst == JMPN) PC = (ACC <  0 ? op : PC);
    else if (inst == JMPP) PC = (ACC >  0 ? op : PC);
    else if (inst == JMPZ) PC = (ACC == 0 ? op : PC);
    else if (inst == LOAD) ACC = mem[op];
    else if (inst == STORE) mem[op] = ACC;
    else if (inst == INPUT) {
      int x; cin >> x;
      mem[op] = x;
    } else if (inst == OUTPUT) {
      cout << "PC <- " << PC << " ACC <- " << ACC;
      cout << " SAIDA: " << mem[op];
      cout << endl;
    } else {
      cout << "SEGMENTATION FAULT - Unknown instruction " << inst << endl;
      exit(1);
    }

    if (inst != OUTPUT) {
      cout << "PC <- " << PC << " ACC <- " << ACC;
      cout << endl;
    }

    // wait for input to continue
    cin.get();
  }
}
