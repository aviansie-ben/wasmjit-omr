/*
 * Copyright 2018 wasmjit-omr project participants
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef JIT_HOOK_HPP
#define JIT_HOOK_HPP

#include "src/common.h"
#include "common.h"

#include <cassert>
#include <functional>
#include <string>

namespace wabt {
namespace interp {
enum class Result;

class DefinedFunc;
class Environment;
class Thread;
}

namespace jit {

struct HookAbilities {
  bool may_trace_call = false;
  bool may_trace_return = false;
  bool may_trace_instr = false;
  bool may_trace_trap = false;

  static HookAbilities full() {
    HookAbilities abilities;

    abilities.may_trace_call = true;
    abilities.may_trace_return = true;
    abilities.may_trace_instr = true;
    abilities.may_trace_trap = true;

    return abilities;
  }
};

struct ThreadHooks {
  std::function<void (interp::Thread*)> on_call;
  std::function<void (interp::Thread*)> on_return;
  std::function<void (interp::Thread*)> on_instr;
  std::function<void (interp::Thread*, interp::Result)> on_trap;

  void validate(const HookAbilities& abilities) {
    assert(!on_call || abilities.may_trace_call);
    assert(!on_return || abilities.may_trace_return);
    assert(!on_instr || abilities.may_trace_instr);
    assert(!on_trap || abilities.may_trace_trap);
  }
};

void JitHookCall(ThreadInfo* thread);
void JitHookReturn(ThreadInfo* thread);
void JitHookInstr(ThreadInfo* thread);
void JitHookTrap(ThreadInfo* thread, Result_t result);

}
}

#endif // JIT_ENVIRONMENT_HPP
