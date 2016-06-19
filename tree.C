#include "tree.H"

#include <algorithm>
#include <iostream>

void Tree::compute_candidates(Edge& e)
{
  Node &n = at(e.head);
  compute_candidates(n);
  for (unsigned i = 0; i < n.size(); i++) {
    e.add(n.at(i).pull_back(e.C, e.R, i));
  }
}

void Tree::compute_candidates(Node& n)
{
  for (Edge &e : n.outgoing) {
    compute_candidates(e);
  }
  switch (n.outgoing.size()) {
    case 0:
      n.add(SolutionCandidate());
      break;
    case 1:
      if (&n == &front()) { // may not insert buffer at root vertex
        for (const SolutionCandidate &s : n.outgoing.front()) {
          n.add(s);
        }
      } else {
        n.buffer(n.outgoing.front(), library);
      }
      break;
    default:
      n.merge(n.outgoing);
  }
}

