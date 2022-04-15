#include <iostream>
#include <string>
#include <sstream>
#include "tree.h"
using namespace std;

int main() {
  string s;
  Tree *t = new Tree;

  while (getline(cin, s)) {
    istringstream ss{s};
    string cmd;
    ss >> cmd;
    if (cmd == "i") {
      int n;
      ss >> n;
      t->insert(n);
    }
    if (cmd == "p") {
      for (auto d : *t) {
        cout << d << endl;
      }
    }
    if (cmd == "c") {
      delete t;
      t = new Tree;
    }
  }
  delete t;
}
