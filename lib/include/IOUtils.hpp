#pragma once

#include <iostream>

#ifdef DEBUG
#define LOG(...) printf(__VA_ARGS__); printf("\n");
#else
#define LOG(...)
#endif

#define OUT_PARAM

template <class Pair>
void print_pair(const Pair& p, std::ostream& out)
{
  out << "(" << p.first << ", " << p.second << ")\n";
}

template <typename First, typename Second>
std::ostream& operator << (std::ostream& out, const std::pair<First, Second>& p)
{
  out << "(" << p.first << ", " << p.second << ")";
  return out;
}

template <class Vector>
void print_vector(const Vector& a, std::ostream& out)
{
  out << "{";
  auto it = a.begin();

  if (it != a.end())
  {
    out << *it;
    ++it;
  }

  for ( ; it != a.end(); ++it)
  {
    out << ", " << *it;
  }

  out << "}\n";
}

template <class Matrix>
void print_matrix(const Matrix& m, std::ostream& out)
{
  out << "{";
  
  auto it = m.begin();

  if (it != m.end())
  {
    out << "\n  ";
    print_vector(*it, out);
    ++it;
  }

  for ( ; it != m.end(); ++it)
  {
    out << "  ";
    print_vector(*it, out);
  }

  out << "}\n";
}
