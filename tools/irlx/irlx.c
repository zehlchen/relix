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

typedef int (*CommandCallbackFunction)(State* self, int argc, char** argv);

typedef struct {
  const char*             name;
  const char*             description;
  CommandCallbackFunction callback;
} Command;

int Command_do_help(State* self, int argc, char** argv);
int Command_do_quit(State* self, int argc, char** argv);

Command commands[] = {{"help", "Print this help message", &Command_do_help},
                      {"quit", "Quit the REPL", &Command_do_quit},
                      {NULL, NULL, NULL}};

CommandCallbackFunction Command_find(const char* buffer)
{
  unsigned long length = strlen(buffer);

  for (int i = 0; commands[i].name; i++) {
    if (strcmp(commands[i].name, buffer) == 0)
      return commands[i].callback;
  }

  return NULL;
}

void Command_split(const char* line, int* argc, char*** argv)
{
  char*  buffer = strdup(line);
  char** tokens = NULL;

  char* token = strtok(buffer, " ");

  while (token) {
    tokens        = realloc(tokens, sizeof(char*) * (*argc + 1));
    tokens[*argc] = strdup(token);
    (*argc)++;
    token = strtok(NULL, " ");
  }

  *argv = tokens;
}

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
    char*  input  = readline("relix> ");
    uint32 length = strlen(input);

    if (!input)
      break;

    add_history(input);

    if (input[0] == '/' && length > 1) {
      int    cmd_argc = 0;
      char** cmd_argv = NULL;

      Command_split(input, &cmd_argc, &cmd_argv);

      CommandCallbackFunction callback = Command_find(*(cmd_argv) + 1);

      callback(state, cmd_argc, cmd_argv);

      free(input);
      continue;
    }

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

int Command_do_help(State* self, int argc, char** argv)
{
  printf("Commands:\n");

  for (int i = 0; commands[i].name; i++)
    printf("  /%s - %s\n", commands[i].name, commands[i].description);

  return 0;
}

int Command_do_quit(State* self, int argc, char** argv)
{
  exit(0);
  return 0;
}