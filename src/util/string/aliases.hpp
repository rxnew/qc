#pragma once

#include "basic_string.hpp"
#include "multi_value.hpp"

namespace qc {
namespace util {
namespace string {
// エイリアス判定クラス
// 大文字小文字を区別しない
template <int N>
using Aliases = MultiValue<CaseInsensitiveString, N>;
}
}
}
