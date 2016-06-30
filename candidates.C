#include "candidates.H"

SolutionCandidate SolutionCandidate::pull_back(unsigned int C, unsigned int R, unsigned int i) const
{
  return SolutionCandidate(0, C+this->C, this->rat-R*(this->C+C/2.), std::vector<unsigned>(1, i));
}

void CandidateList::add(const SolutionCandidate& s)
{
  if (empty() || back().rat < s.rat) {
    push_back(s);
  }
}

void CandidateList::buffer(const CandidateList& e, const std::vector<Buffer> &l)
{
  // consider candidates and buffers ascending by capacity
  typename CandidateList::const_iterator it = e.begin();
  for (const Buffer &b : l) {
    // find the optimal candidate t to buffer with b and call the buffered version s
    SolutionCandidate s(1 + &b - &l.front(), b.C, -std::numeric_limits<double>::infinity(), std::vector<unsigned>());
    for (const SolutionCandidate &t : e) {
      double rat = t.rat - b.R*t.C;
      if (rat > s.rat) {
        s.rat = rat;
        s.used = t.used;
      }
    }
    while (it != e.end() && it->C < s.C) {
      add(*it++);
    }
    if (it != e.end() && it->C == s.C) { // special case use better for equal capacity take better one
      if (it->rat < s.rat) {
        add(s);
        it++;
      } else {
        add(*it++);
      }
    } else { // normal case use s unless it's allready dominated
      add(s);
    }
  }
  while (it != e.end()) {
    add(*it++);
  }
}