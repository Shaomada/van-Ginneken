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
  // consider all buffered and unbuffered SolutionCandidates ascending by C
  const SolutionCandidate &t = e.back();
  typename CandidateList::const_iterator it = e.begin();
  for (unsigned i = 0; i < l.size(); i++) {
    SolutionCandidate s(i+1, l.at(i).C, s.rat - l.at(i).R*t.C, t.used);
    while (it != e.end() && it->C < s.C) {
      add(*it++);
    }
    if (it != e.end() && it->C == s.C) { // special case
      if (it->rat < s.rat) {
        add(s);
        it++;
      } else {
        add(*it++);
      }
    } else { // normal case
      add(s);
    }
  }
  while (it != e.end()) {
    add(*it++);
  }
}