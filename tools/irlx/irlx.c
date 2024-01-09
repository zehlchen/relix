#include <compiler/compiler.h>
#include <io/io.h>
#include <runtime/runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <vm/eval.h>
#include <vm/module.h>

#include "version.h"

// GNU readline
#include <readline/history.h>
#include <readline/readline.h>

int main(int argc, char** argv)
{
  relix_print_version();
  relix_print_copyright();

  printf("\n");

  runtime_init();

  Module*  module  = Module_new();
  Context* context = Compiler_newContext(module);

  State* state = State_new(module);
  State_setGlobalState(state);

  while (1) {
    char* input = readline("relix> ");

    if (!input)
      break;
    add_history(input);

    int block = Compiler_compileString(context, input);

    if (block >= 0) {
      Object* object = eval(state, block, 0);

      printf("=> ");
      io_print(0, object);
    }
    free(input);
  }

  Compiler_deleteContext(context);
  State_delete(state);
  Module_delete(module);

  return 0;
}
