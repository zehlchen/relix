#include <compiler/compiler.h>
#include <runtime/runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vm/eval.h>
#include <vm/module.h>

void version()
{
  fputs("RELIX " VERSION " " BUILD_TYPE " (" __DATE__ ", " __TIME__ ")\n", stderr);
#ifdef GIT_VERSION
  fputs("[" GIT_VERSION "]\n", stderr);
#endif

  fputs("\n" COPYRIGHT "\n", stderr);
}

void help()
{
  fputs("Usage: relix [options ...] [input file]\n"
        "  --help, -h   Shows this message\n"
        "  -c           Compile to bytecode\n"
        "  -d           Dump bytecode\n"
        "  -o [file]    Set the output filename\n"
        "  --version    Shows version information\n"
        "  --           Stop reading options\n",
        stderr);
}

int main(int argc, const char** argv)
{
  int         compile  = 0;
  int         dump     = 0;
  const char* filename = 0;
  const char* output   = 0;

  for (int count = 1; count < argc; count++) {
    if (argv[count][0] == '-') {
      if (!strcmp(argv[count], "-c")) {
        compile = 1;
      }
      else if (!strcmp(argv[count], "-d")) {
        dump = 1;
      }
      else if (!strcmp(argv[count], "-h")) {
        help();
        return 0;
      }
      else if (!strcmp(argv[count], "--help")) {
        help();
        return 0;
      }
      else if (!strcmp(argv[count], "-o")) {
        output = argv[++count];
      }
      else if (!strcmp(argv[count], "--version")) {
        version();
        return 0;
      }
      else if (!strcmp(argv[count], "--")) {
        break;
      }
      else {
        help();
        fprintf(stderr, "relix: invalid option %s", argv[count]);
        return 1;
      }
    }
    else {
      filename = argv[count];
      break;
    }
  }

  runtime_init();

  FILE* file = filename ? fopen(filename, "r") : stdin;

  if (!file) {
    fprintf(stderr, "relix: %s: no such file\n", filename);
    return 1;
  }

  Module* module;
  int     blockId = 0;
  if (Module_probe(file)) {
    module = Module_read(file);
  }
  else {
    module           = Module_new();
    Context* context = Compiler_newContext(module);
    blockId          = Compiler_compileFile(context, file);
    Compiler_deleteContext(context);
    if (blockId < 0)
      return 1;
  }

  if (compile) {
    // generate the output filename if it's not specified
    if (!output) {
      if (!filename) {
        output = "out.rlx";
      }
      else {
        char* outf;
        int   len = strlen(filename);

        if (!strcmp(filename + len - 3, ".rr")) {
          outf = malloc(sizeof(char) * len + 2);
          strncpy(outf, filename, len - 3);
          outf[len - 3] = '\0';
        }
        else {
          outf = malloc(sizeof(char) * len + 5);
          strcpy(outf, filename);
        }

        strcat(outf, ".rlx");
        output = (const char*) outf;
      }
    }

    FILE* out = fopen(output, "w");
    Module_write(module, out);
  }
  else if (dump) {
    Module_dump(module);
  }
  else {
    State* state = State_new(module);
    State_setGlobalState(state);
    eval(state, blockId, 0);
    State_delete(state);
  }

  Module_delete(module);

  return 0;
}
