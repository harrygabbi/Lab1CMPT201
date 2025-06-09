#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  pid_t pid;
  int status;

  printf("Enter programs to run.\n");
  while (1) {
    printf("> ");
    nread = getline(&line, &len, stdin);
    if (nread < 0) {

      break;
    }

    if (line[nread - 1] == '\n') {
      line[nread - 1] = '\0';
    }

    if (line[0] == '\0' || strcmp(line, "exit") == 0) {
      break;
    }

    pid = fork();
    if (pid < 0) {
      perror("fork");
      break;
    }
    if (pid == 0) {

      execl(line, line, (char *)NULL);

      fprintf(stderr, "Exec failure\n");
      exit(1);
    } else {
      if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
      }
    }
  }

  free(line);
  return 0;
}
