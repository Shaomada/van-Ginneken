#ifndef INCLUDED_TREE_H
#define INCLUDED_TREE_H

#include "candidates.H"

struct Edge : public CandidateList {
  inline Edge (unsigned head, unsigned C, unsigned R)
    : CandidateList(), head(head), C(C), R(R) { }
  const unsigned head;
  const unsigned C;
  const unsigned R;
};

struct Node : public CandidateList {
  inline Node () : CandidateList(), outgoing() { }
  std::vector<Edge> outgoing;
  
  void print(unsigned i, unsigned depth = 0);
};

struct Tree : std::vector<Node> {
  Tree (unsigned n) : std::vector<Node>(n), root (0, 0, 1), library() { }
  void compute_candidates (Edge &e);
  void compute_candidates(Node &n);
  void search(std::map<unsigned, unsigned> output, unsigned n_id, unsigned c_id) const;
  
  Edge root;
  std::vector<Buffer> library;
};

#endif

