#ifndef INCLUDED_BUFFER_H
#define INCLUDED_BUFFER_H

struct Buffer {
  unsigned C;
  unsigned R;
  bool operator< (const Buffer &other) const { return C < other.C || (C == other.C && R < other.R); } // for sorting library
};

#endif