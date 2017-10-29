/* A parser using conventional infix notations */
#include "mpc.h"

#ifdef _WIN32

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* Fake add_history function */
void add_history(char* unused) {}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv) {

  /* Create some parsers */
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  /* Define the grammar */
  mpca_lang(
    MPCA_LANG_DEFAULT,
    " \
      number : /-?[0-9]+/ ; \
      operator : '+' | '-' | '*' | '/'; \
      expr: <number> | '(' <expr> <operator> <expr> ')' ; \
      lispy : /^/ <expr> <operator> <expr> /$/ ; \
    ",
    Number, Operator, Expr, Lispy);

  /* Print version and some help */
  puts("Lispy Version 0.0.0.0.2i");
  puts("Press Ctrl-C to Exit\n");

  while (1) {
    /* Output the prompt and get input */
    char* input = readline("lispy>> ");

    /* Add input to history */
    add_history(input);

    /* Attempt to parse the user input */
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }

  /* Undefine and delete the parsers */
  mpc_cleanup(4, Number, Operator, Expr, Lispy);

  return 0;
}
