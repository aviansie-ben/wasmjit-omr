#ifndef JIT_COMMON_HPP
#define JIT_COMMON_HPP

#include "src/common.h"

#include <cstdint>

namespace wabt {
namespace jit {

struct ThreadInfo;

using Result_t = int32_t;
using JITedFunction = Result_t (*)(ThreadInfo*, Index);

}
}

#endif // JIT_COMMON_HPP
