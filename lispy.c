#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

static char input[2048];

int main(int argc, char** argv) {
  /* Print version and some help */
  puts("Lispy Version 0.0.1");
  puts("Press Ctrl-C to Exit\n");

  while (1) {
    /* Output the prompt and get input */
    char* input = readline("lispy>> ");

    /* Echo input back to user */
    printf("You said %s\n", input);
    free(input)
  }

  return 0;
}
