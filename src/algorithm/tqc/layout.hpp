/**
 * @file layout.hpp
 * @brief header of Layout class
 */

#pragma once

namespace qc {
inline namespace algorithm {
inline namespace tqc {
class Layout {
 public:
  std::map<BitNo, Vec> coords_;
  int height_;
  int width_;
  Layout();
  Layout(CnotCircuit* circ, bool two_dim = true);
  Layout(const Layout& other);
  ~Layout();
  Layout& operator=(const Layout& other);
  bool operator==(const Layout& other) const;
  bool operator!=(const Layout& other) const;
  Vec& operator[](BitNo bit);
  const Vec& operator[](BitNo bit) const;
  inline std::map<BitNo, Vec>::size_type size() const {return this->coords_.size();}
  std::vector<BitNo> getBitOrder() const;
  void print(std::ostream& os) const;
  void output(const char* filename) const;
  void output(const std::string& filename) const;
  bool input(const char* filename);
  bool input(const std::string& filename);
};
