#include "../x.hpp"

namespace qc {
constexpr char const* const X::TYPE_NAME = "X";
constexpr util::string::Aliases<5> const X::ALIASES = {
  "x",
  "not",
  "toffoli",
  "mct",
  "mpmct"
};
}
