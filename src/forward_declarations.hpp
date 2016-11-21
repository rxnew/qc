#pragma once

#include <list>
#include <unordered_set>
#include <unordered_map>

namespace qc {
class Bit;
class CBit;
class TBit;
class Gate;
class Circuit;

using BitNo = unsigned int;
using BitNos = std::unordered_set<BitNo>;
using CBits = std::unordered_set<CBit>;
using TBits = std::unordered_set<TBit>;
using Gates = std::list<Gate>;
using GatesIter = Gates::iterator;
using GatesCIter = Gates::const_iterator;
}
