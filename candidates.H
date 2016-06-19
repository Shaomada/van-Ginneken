#ifndef INCLUDED_CANDIDATES_H
#define INCLUDED_CANDIDATES_H

#include "buffer.H"

#include <vector>
#include <limits>
#include <algorithm>

struct SolutionCandidate {
  inline SolutionCandidate(unsigned b, unsigned C, double rat, std::vector<unsigned> used)
    : b(b), C(C), rat(rat), used(used) { }
  inline SolutionCandidate() : SolutionCandidate(0, 1, 0, std::vector<unsigned>()) { }

  /// pull back the \param i -th Candidate of a list through an Edge of Capacacity C and Resitance R
  SolutionCandidate pull_back(unsigned C, unsigned R, unsigned i) const;

  unsigned b;
  unsigned C;
  double rat;
  std::vector<unsigned> used;
};

/// A list of SolutionCandidates with rat and C strictly ascending
struct CandidateList : public std::vector<SolutionCandidate> {
  inline CandidateList () : std::vector<SolutionCandidate>() { }

  /// Checks rat instead of simpling using push_back.
  void add (const SolutionCandidate &s);

  /// Buffers the SolutionCandidates beloning to the single outgoing Edge of an Vertex.
  void buffer (const CandidateList &e, const std::vector<Buffer> &l);

  /// Merges the SolutionCandidates beloning to outgoing Edges of an Vertex
  template <typename Edge>
  void merge (const std::vector<Edge> &v);
};

template <typename Edge>
void CandidateList::merge(const std::vector< Edge >& v)
{
  // consider ascending by rat all SolutionCandidates with minimal C for current rat
  std::vector<typename Edge::const_iterator> its;
  for (const Edge &l : v) {
    its.push_back(l.begin());
  }
  while(true) {
    SolutionCandidate s(0, 0, std::numeric_limits<double>::infinity(), std::vector<unsigned>());
    for (const typename Edge::const_iterator &it : its) {
      s.C += it->C;
      s.rat = std::min (s.rat, it->rat);
      for (unsigned i : it->used) {
        s.used.push_back(i);
      }
    }
    push_back(s);
    for (unsigned i = 0; i < its.size(); i++) {
      typename Edge::const_iterator &it = its.at(i);
      if (it->rat == s.rat) {
        ++it;
        if (it == v.at(i).end()) {
          return;
        }
      }
    }  
  }
}

#endif