#pragma once

#define STR(arg) #arg

namespace qc {
enum class GateType {
  Group,
  U,
  I,
  H,
  X,
  Y,
  Z,
  V,
  VDagger,
  W,
  WDagger,
  S,
  SDagger,
  T,
  TDagger,
  Swap,
};
}
