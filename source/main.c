#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cli.h>

int main(int argc, char **argv) {
  if ((argc >1 && !strncmp(argv[1], "help", 4)) || argc == 1) {
    help();
    exit(1);
  }

  if (argc != 3) {
    fprintf(stderr, "No expression provided: expr argument is (nil)\n");
    exit(69);
  }

  char *cli_operation = argv[1];

  for (size_t i=0; i<sizeof(operations)/sizeof(operations[0]); ++i) {
    if (!strncmp(cli_operation, operations[i], strlen(operations[i]))) {
      actions[i](argv[2]);
      return EXIT_SUCCESS;
    }
  }
  fprintf(stderr, "Operation '%s' is not supported\n", cli_operation);
  exit(69);
}
