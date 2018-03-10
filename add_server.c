#include "add.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void child_proc() {
  execl("./ext_add", "ext_add", "", (char *) 0);
}

void parent_proc(int a, int b, int* result) {
  // Read the result from child process
  char raw_result[100];
  printf("%d\n", a);
  printf("%d\n", b);
  read(STDIN_FILENO, raw_result, 100); // We get a result like "Enter a: Enter b: Result: 8"

  // Parse the result
  char *result_ptr = strstr(raw_result, "Result: ");
  result_ptr+=8;
  *result = atoi(result_ptr);
}

void sum_from_ext_program(int a, int b, int* result) {
  int pipeEnds1[2];
  int pipeEnds2[2];
  pipe(pipeEnds1);
  pipe(pipeEnds2);
  printf("A call is made by the client.\n");
  pid_t pid = fork();
  if(pid == 0) {
    // Child process pipes
    dup2(pipeEnds1[1], STDOUT_FILENO);
    close(pipeEnds1[1]);
    close(pipeEnds1[0]);
    dup2(pipeEnds2[0], STDIN_FILENO);
    close(pipeEnds2[1]);
    close(pipeEnds2[0]);
    child_proc();
  } else if (pid < 0) {
    printf("ERROR ON FORK\n");
    exit(1);
  } else {
    // int childReturn;
    // waitpid(pid, &childReturn, 0);
    // Parent process pipes
    dup2(pipeEnds2[1], STDOUT_FILENO);
    close(pipeEnds2[1]);
    close(pipeEnds2[0]);
    dup2(pipeEnds1[0], STDIN_FILENO);
    close(pipeEnds1[1]);
    close(pipeEnds1[0]);
    //parent_proc(a, b, result);

    // Read the result from child process
    char raw_result[100];
    printf("%d\n", a);
    printf("%d\n", b);
    read(STDIN_FILENO, raw_result, 100); // We get a result like "Enter a: Enter b: Result: 8"

    // Parse the result
    char *result_ptr = strstr(raw_result, "Result: ");
    result_ptr+=8;
    *result = atoi(result_ptr);
    // *result = 6;
  }
}

int *
add_1_svc(intpair *argp, struct svc_req *rqstp)
{
        static int result = -1;
        sum_from_ext_program(argp->a, argp->b, &result);
	//printf("Result: %s\n", resultStr);
	return &result;
}
