#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

#include "candidates.H"
#include "tree.H"

int main (int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " FILENAME" << std::endl;
    return 1;
  }

  std::ifstream input ( argv[1] );
  unsigned x[5];
  input >> x[4];
  Tree t(x[4]);
  for (unsigned i = 1; i < x[4]; i++) {
    input >> x[0] >> x[1] >> x[2] >> x[3];
    t.at(x[0]).outgoing.emplace_back(x[1], x[2], x[3]);
  }
  input >> x[2];
  for (unsigned i = 0; i < x[2]; i++) {
    input >> x[0] >> x[1];
    t.library.push_back({x[0], x[1]});
  }
  std::sort(&t.library.front(), &t.library.front()+x[2]);

  t.compute_candidates(t.root);
  std::map<unsigned, unsigned> buffers_used;
  t.search(buffers_used, 0, t.front().size()-1);
  std::cout << t.root.back().rat << " " << buffers_used.size() << std::endl;
  for (const auto &pair : buffers_used) {
    std::cout << pair.first << " " << pair.second << std::endl;
  }
  return 0;
}