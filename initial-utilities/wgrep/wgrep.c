#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS_EXIT 0
#define ERROR_EXIT 1

#define LINE_SIZE 256

int main(int argc, char *argv[]) {
  if (argc < 2) {
    // spec from README
    printf("wgrep: searchterm [file ...]\n");
    exit(ERROR_EXIT);
  }

  FILE *stream;
  char *searchTerm = argv[1];
  // if line is set to NULL before the call, then getline() will allocate a
  // buffer for storing the line
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  if (argc == 2) { // read from stdin
    /* while (fgets(line, (LINE_SIZE + 1), stdin) != NULL) { */
    /*   if (line != NULL && strstr(line, searchTerm) != NULL) { */
    /*     printf("%s", line); */
    /*   } */
    /* } */
    while ((nread = getline(&line, &len, stdin)) != -1) {
      if (strstr(line, searchTerm) != NULL) {
        printf("%s", line);
      }
    }

    free(line);
  } else {
    for (int i = 2; i < argc; ++i) {
      stream = fopen(argv[i], "r");
      if (stream == NULL) {
        printf("wgrep: cannot open file\n");
        exit(ERROR_EXIT);
      }

      while ((nread = getline(&line, &len, stream)) != -1) {
        if (strstr(line, searchTerm) != NULL) {
          printf("%s", line);
        }
      }

      free(line);
      fclose(stream);
    }
  }

  exit(SUCCESS_EXIT);
}
