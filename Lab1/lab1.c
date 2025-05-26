#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *line = NULL;
  size_t len = 0;

  printf("Please enter text: ");

  ssize_t read = getline(&line, &len, stdin);
  if (read == -1) {
    perror("getline failed");
    free(line);
    return 1;
  }

  printf("Tokens\n");
  char *saveptr;
  char *token = strtok_r(line, " \n", &saveptr);

  while (token != NULL) {
    printf("  %s\n", token);
    token = strtok_r(NULL, " \n", &saveptr);
  }

  free(line);
  return 0;
}
