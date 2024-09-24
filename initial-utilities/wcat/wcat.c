#include <stdio.h>
#include <stdlib.h>

/*
  To read:
  [X] man fopen
  [X] man fgets
  [X] man fclose
*/

#define SUCCESS_EXIT 0
#define ERROR_EXIT 1

/* We assume that the file this program is reading is a text file and that lines
 * in this text file are no longer than 1024 bytes long. */
#define LINE_SIZE 256

int main(int argc, char **argv) {
  if (argc < 2) {
    /* printf("USAGE: wcat <path1> <path2> ..."); */
    return SUCCESS_EXIT;
  }

  char *buffer;
  buffer = malloc(sizeof(char) * (LINE_SIZE + 1));
  for (int i = 1; i < argc; ++i) {
    char *pathname = argv[i];

    FILE *f = fopen(pathname, "r");
    if (f == NULL) {
      printf("wcat: cannot open file\n");
      return ERROR_EXIT;
    }

    while (fgets(buffer, LINE_SIZE + 1, f) != NULL) {
      if (buffer != NULL) {
        printf("%s", buffer);
      }
    }

    int c = fclose(f);
    if (c != 0) {
      printf("wcat: cannot open file\n");
      return ERROR_EXIT;
    }
  }
  if (buffer != NULL) {
    free(buffer);
  }

  return SUCCESS_EXIT;
}
