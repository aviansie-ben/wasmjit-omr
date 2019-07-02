#include "hook.h"
#include "thread.h"
#include "src/interp/interp.h"

#include <iostream>

namespace wabt {
namespace jit {

void JitHookCall(ThreadInfo* thread) {
  auto& hook = thread->thread->ThreadHooks().on_call;
  if (hook) {
    thread->thread->set_pc(thread->pc);
    thread->thread->call_stack_top_ = thread->call_stack - thread->thread->call_stack_.data();

    hook(thread->thread);
  }
}

void JitHookReturn(ThreadInfo* thread) {
  auto& hook = thread->thread->ThreadHooks().on_return;
  if (hook) {
    thread->thread->set_pc(thread->pc);
    thread->thread->call_stack_top_ = thread->call_stack - thread->thread->call_stack_.data();

    hook(thread->thread);
  }
}

void JitHookInstr(ThreadInfo* thread) {
  auto& hook = thread->thread->ThreadHooks().on_instr;
  if (hook) {
    thread->thread->set_pc(thread->pc);
    thread->thread->call_stack_top_ = thread->call_stack - thread->thread->call_stack_.data();

    hook(thread->thread);
  }
}

void JitHookTrap(ThreadInfo* thread, Result_t result) {
  auto& hook = thread->thread->ThreadHooks().on_trap;
  if (hook) {
    thread->thread->set_pc(thread->pc);
    thread->thread->call_stack_top_ = thread->call_stack - thread->thread->call_stack_.data();

    hook(thread->thread, static_cast<interp::Result>(result));
  }
}

}
}
