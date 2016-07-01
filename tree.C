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

void Tree::search(std::map< unsigned, unsigned > &output, unsigned int n_id, unsigned c_id) const
{
  const Node &n = at(n_id);
  const SolutionCandidate &s = n.at(c_id);
  if (s.b != 0) {
    output.emplace(n_id, s.b);
  }
  for (unsigned i = 0; i < s.used.size(); i++) {
    search(output, n.outgoing.at(i).head, s.used.at(i));
  }
}
